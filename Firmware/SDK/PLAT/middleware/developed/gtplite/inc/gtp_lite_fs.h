/******************************************************************************
 ******************************************************************************
 Copyright:      - 2021- Copyrights of Qualcomm Inc.
 File name:      - gtp_conn.c
 Description:    - GTP transport Layer sub-module
 History:        - 19/08/2021
 ******************************************************************************
******************************************************************************/
#ifndef __GTP_LITE_FS_H__
#define __GTP_LITE_FS_H__

#include "lfs_port.h"

#define O_RDONLY             LFS_O_RDONLY
#define O_WRONLY             LFS_O_WRONLY
#define O_RDWR               LFS_O_RDWR
#define O_CREAT              LFS_O_CREAT
#define O_EXCL               LFS_O_EXCL
#define O_TRUNC              LFS_O_TRUNC
#define O_APPEND             LFS_O_APPEND

typedef lfs_ssize_t gtp_fs_ssize_t;
typedef lfs_size_t gtp_fs_size_t;
typedef lfs_soff_t gtp_fs_off_t;
typedef struct lfs_info gtp_fs_stat;

static inline int gtp_fs_open(const char *path, int oflag, ...)
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

static inline gtp_fs_ssize_t gtp_fs_read (int filedes, void *buf, gtp_fs_size_t nbyte)
{
	gtp_fs_ssize_t ret = 0;

	if (filedes <= 0) return -1;
	ret =LFS_FileRead((lfs_file_t *)filedes, buf, nbyte);

	return ((ret < 0) ? -1 : ret);
}

static inline gtp_fs_ssize_t gtp_fs_write (int filedes, const void *buf, gtp_fs_size_t nbyte)
{
	gtp_fs_ssize_t ret;

	if (filedes <= 0) return -1;
	ret = LFS_FileWrite((lfs_file_t *)filedes, buf, nbyte);

	return ((ret < 0) ? -1 : ret);
}

static inline int gtp_fs_close (int filedes)
{
	int ret = 0;

	if (filedes <= 0) return -1;
	ret = LFS_FileClose((lfs_file_t *)filedes);
	free((void *)filedes);

	return ((ret < 0) ? -1 : ret);
}

static inline int gtpfs_stat (const char *path, gtp_fs_stat *buf)
{
	int ret = 0;
	ret = LFS_Stat(path, buf);
	return ((ret < 0) ? -1 : ret);
}

static inline int gtp_fs_unlink (const char *path)
{
	int ret = 0;
	ret = LFS_Remove(path);
	return ((ret < 0) ? -1 : ret);
}
#endif
