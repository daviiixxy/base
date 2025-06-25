#ifndef _QURT_FS_H
#define _QURT_FS_H

#include "lfs_port.h"
#include "cmsis_os2.h"

#define O_RDONLY             LFS_O_RDONLY
#define O_WRONLY             LFS_O_WRONLY
#define O_RDWR               LFS_O_RDWR
#define O_CREAT              LFS_O_CREAT
#define O_EXCL               LFS_O_EXCL
#define O_TRUNC              LFS_O_TRUNC
#define O_APPEND             LFS_O_APPEND

typedef lfs_ssize_t fs_ssize_t;
typedef lfs_size_t fs_size_t;
typedef lfs_soff_t fs_off_t;
typedef struct lfs_info fs_stat;

static inline int efs_open(const char *path, int oflag, ...)
{
	lfs_file_t *fileH = NULL;
	fileH = calloc(1,sizeof(lfs_file_t));
	if (fileH == NULL)return -1;
	if (0 != LFS_FileOpen(fileH, path, oflag))
	{
		free(fileH);
		return -1;
	}
	return (int)fileH;
}

static inline fs_ssize_t efs_read (int filedes, void *buf, fs_size_t nbyte)
{
	fs_ssize_t ret = 0;

	if (filedes <= 0) return -1;
	ret =LFS_FileRead((lfs_file_t *)filedes, buf, nbyte);

	return ((ret < 0) ? -1 : ret);
}

static inline fs_ssize_t efs_write (int filedes, const void *buf, fs_size_t nbyte)
{
	fs_ssize_t ret;

	if (filedes <= 0) return -1;
	ret = LFS_FileWrite((lfs_file_t *)filedes, buf, nbyte);

	return ((ret < 0) ? -1 : ret);
}

static inline fs_off_t efs_lseek (int filedes, fs_off_t offset, int whence)
{
	fs_off_t ret;
	
	if (filedes <= 0) return -1;
	ret = LFS_FileSeek((lfs_file_t *)filedes, offset, whence);

	return ((ret < 0) ? -1 : ret);
}

static inline int efs_close (int filedes)
{
	int ret = 0;

	if (filedes <= 0) return -1;
	ret = LFS_FileClose((lfs_file_t *)filedes);
	free((void *)filedes);

	return ((ret < 0) ? -1 : ret);
}

static inline int efs_stat (const char *path, fs_stat *buf)
{
	int ret = 0;
	ret = LFS_Stat(path, buf);
	return ((ret < 0) ? -1 : ret);
}

static inline int efs_unlink (const char *path)
{
	int ret = 0;
	ret = LFS_Remove(path);
	return ((ret < 0) ? -1 : ret);
}
#endif //_QURT_FS_H
