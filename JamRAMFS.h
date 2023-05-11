
#ifndef core_JamFS_h
#define core_JamFS_h

enum returnCode { OK, NO };

/**
 @param name
 this will be strcpy()'d
 */
enum returnCode create(char * name, char * path, int path_length, char res_type);

int write_file(char * path, char * name, const char * fileContent);

enum returnCode delete(char *path, char *name);

enum returnCode read_file(char * path, char * name, char * fileContent);

struct jiletag {
    int allowedRead;
    int allowedWrite;
    unsigned char *fileDataBuffer;
    size_t pos;
    size_t sz;
    size_t memsz;
    int areWeAllowedToReallocIt;
    void* priv;
};
typedef struct jiletag JILE;
/**
 
  @param mode
 | mode string | r | r+ | w | w+ | a | a+ |
 |-------------|---|----|---|----|---|----|
 |reading      | x | x  |   | x  |   | x  |
 |writing      |   | x  | x | x  | x | x  |
 |create new   |   |    | x | x  | x | x  |
 |overwrite    |   |    | x | x  |   |    |
 |open at start| x | x  | x | x  |   |    |
 |open at end  |   |    |   |    | x | x  |

 
 */
JILE *jopen(const char *filename, const char *mode);
int j_open(const char *path, int flags);
/**
 sets the file position
 @param whence
 it should be SEEK_SET, SEEK_CUR, or SEEK_END
 @return it returns negative on error
 @retval 0 okay
 @retval -1 error
*/
int jseek(JILE* stream, long offset, int whence);

#define J_RDONLY (1<<1)
#define J_WRONLY (1<<2)
#define J_RDWR   (J_RDONLY|J_WRONLY)
#define J_CREAT (1<<3)
#define J_TRUNC (1<<4)
/**
@return the current file position of the given stream.
*/
long int jtell(JILE * stream);

/**
give file descriptor, get FILE*, but jamos variant
@return NULL on error, else the JILE*
*/
JILE* jdopen(int fd, const char* mode);

/**
give FILE*, get file descriptor, but jamos variant
@return -1 on error, else the file descriptor
*/
int jileno(const JILE* stream);

/**
blkcnt_t and off_t shall be signed integer types.
*/
#ifndef __off_t_defined
#ifndef __USE_FILE_OFFSET64
typedef long off_t;
#else
typedef long long off_t;
#endif
#define __off_t_defined
#endif 
off_t jlseek(int fd, off_t offset, int whence);

/**
just as a fallback so this can be used without
VirtDir dependancy
@return negative on failure
@retval 0
okay
@retval -1
bad
*/
int jremove(const char* const path);
int jkdir(const char* filename, int mode);

#endif//core_JamFS_h

