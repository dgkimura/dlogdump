#include "postgres.h"

#include <unistd.h>

#include "access/distributedlog.h"
#include "pg_config.h"
#include "access/slru.h"
#include "access/transam.h"

#define ENTRIES_PER_PAGE (BLCKSZ / sizeof(DistributedLogEntry))
#define TransactionIdToPage(localXid) ((localXid) / (TransactionId) ENTRIES_PER_PAGE)

int
main(int argc, char** argv)
{
	TransactionId indexXid;
	DistributedTransactionTimeStamp distribTimeStamp;
	DistributedTransactionId distribXid;

	int pageno = TransactionIdToPage(FirstNormalTransactionId);
	int segno = pageno / SLRU_PAGES_PER_SEGMENT;
	int rpageno = pageno % SLRU_PAGES_PER_SEGMENT;
	int offset = rpageno * BLCKSZ;

	/*
	 * 1. open dlog file: BasicOpenFile()
	 */
	int fd = open("dlog", O_RDWR | PG_BINARY, S_IRUSR | S_IWUSR);

	/*
	 * 2. load dlog contents: lseek(), read(), close()
	 */
	if (lseek(fd, (off_t) offset, SEEK_SET) < 0)
	{
		close(fd);
		return -1;
	}

	char buffer[BLCKSZ];
	if (read(fd, buffer, BLCKSZ) != BLCKSZ)
	{
		close(fd);
		return -1;
	}

	if (close(fd))
	{
		return -1;
	}

	/*
	 * 3. Iterate over the contents.
	 */
}
