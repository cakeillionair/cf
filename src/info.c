#include "info.h"

char *fmtinfo(char *path, char *file, char *buf, bool color) {
    if (buf == NULL) return NULL;

    struct stat statbuf;

    char fullpath[PATH_MAX];
    sprintf(fullpath, "%s/%s", path, file);
    if (stat(fullpath, &statbuf) != 0) {
        sprintf(buf,
            "%sxxxxxxxxxx xxxx xxxx xxxxxxxxx xxxx xxx xx %s%s\n"
            , (color) ? RED_F : ""
            , file
            , (color) ? DEFAULT_F : ""
        );
        return buf;
    }
    
    char mode[11];
    mode[0] = S_ISDIR(statbuf.st_mode) ? 'd' : FILLER;
	
	mode[1] = (statbuf.st_mode & 0400) ? 'r' : FILLER;
	mode[2] = (statbuf.st_mode & 0200) ? 'w' : FILLER;
	mode[3] = (statbuf.st_mode & 0100) ? 'x' : FILLER;
	
	mode[4] = (statbuf.st_mode & 0040) ? 'r' : FILLER;
	mode[5] = (statbuf.st_mode & 0020) ? 'w' : FILLER;
	mode[6] = (statbuf.st_mode & 0010) ? 'x' : FILLER;
	
	mode[7] = (statbuf.st_mode & 0004) ? 'r' : FILLER;
	mode[8] = (statbuf.st_mode & 0002) ? 'w' : FILLER;
	mode[9] = (statbuf.st_mode & 0001) ? 'x' : FILLER;
    
    char time[32];
    struct tm *tinfo = localtime(&statbuf.st_mtime);
    strftime(time, sizeof(time), "%Y %b %d %H:%M", tinfo);

    bool isdir = S_ISDIR(statbuf.st_mode);
    bool executable = (statbuf.st_mode & 0111);

    sprintf(buf,
        "%s%s"" ""%s% 4d % 4d"" ""%s% 9ld"" ""%s%s"" ""%s%s%s""%c\n"
        , (color) ? MAGENTA_F : ""
        , mode
        , (color) ? CYAN_F : ""
        , statbuf.st_uid, statbuf.st_gid
        , (color) ? MAGENTA_F : ""
        , statbuf.st_size
        , (color) ? CYAN_F : ""
        , time
        , (color) ? ((isdir) ? BLUE_F : (executable ? GREEN_F : WHITE_F)) : ""
        , file
        , (color) ? DEFAULT_F : ""
        , (isdir) ? '/' : (executable ? '*' : ' ')
    );

    return buf;
}