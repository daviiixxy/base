#ifndef LFS_PORT_H
#define LFS_PORT_H

#include "lfs.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _lfs_status
{
    uint32_t total_block;
    uint32_t block_used;
    uint32_t block_size;
} lfs_status_t;

typedef struct _file_operation_statistic_result
{
    const char* name;
    uint32_t writeCount;
    uint32_t writeBytesCount;
} file_operation_statistic_result_t;

int LFS_GetFileWriteMonitorResult(file_operation_statistic_result_t* result);
int LFS_GetBlockEraseCountResult(uint32_t* result);
int LFS_ResetMonitorResult(void);

// Initialize
int LFS_Init(void);

// Deinit
void LFS_Deinit(void);

// Wrapper of lfs_format
int LFS_Format(void);

// Wrapper of lfs_stat
int LFS_Stat(const char *path, struct lfs_info *info);

// Wrapper of lfs_remove
int LFS_Remove(const char *path);

// Wrapper of lfs_file_open
int LFS_FileOpen( lfs_file_t *file, const char *path, int flags);

// Wrapper of lfs_file_close
int LFS_FileClose(lfs_file_t *file);

// Wrapper of lfs_file_read
lfs_ssize_t LFS_FileRead(lfs_file_t *file, void *buffer, lfs_size_t size);

// Wrapper of lfs_file_write
lfs_ssize_t LFS_FileWrite(lfs_file_t *file, const void *buffer, lfs_size_t size);

// Wrapper of lfs_file_sync
int LFS_FileSync(lfs_file_t *file);

// Wrapper of lfs_file_seek
lfs_soff_t LFS_FileSeek(lfs_file_t *file, lfs_soff_t off, int whence);

// Wrapper of lfs_file_truncate
int LFS_FileTruncate(lfs_file_t *file, lfs_off_t size);

// Wrapper of lfs_file_tell
lfs_soff_t LFS_FileTell(lfs_file_t *file);

// Wrapper of lfs_file_rewind
int LFS_FileRewind(lfs_file_t *file);

// Wrapper of lfs_file_size
lfs_soff_t LFS_FileSize(lfs_file_t *file);

// Wrapper of lfs_dir_open
int LFS_DirOpen(lfs_dir_t *dir, const char *path);

// Wrapper of lfs_dir_close
int LFS_DirClose(lfs_dir_t *dir);

// Wrapper of lfs_dir_read
int LFS_DirRead(lfs_dir_t *dir, struct lfs_info *info);


// Get fs status
int LFS_Statfs(lfs_status_t *status);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
