#include "info.h"

char *fmtinfo(char *path, char *file, char *buf, bool color) {
    if (buf == NULL) return NULL;

    struct stat statbuf;

    char fullpath[PATH_MAX];
    sprintf(fullpath, "%s/%s", path, file);
    if (lstat(fullpath, &statbuf) != 0) {
        sprintf(buf,
            "%sxxxxxxxxxx xxxx xxxx xxxxxxxxx xxxx xxx xx %s%s\n"
            , (color) ? RED_F : ""
            , file
            , (color) ? DEFAULT_F : ""
        );
        return buf;
    }
    
    char *file_color;

    char mode[11];
    mode[0] = FILLER;
    bool special = false;
    if (S_ISDIR(statbuf.st_mode)) {
        mode[0] = 'd';
        file_color = BLUE_F;
        special = true;
    }
    if (S_ISLNK(statbuf.st_mode)) {
        mode[0] = 'l';
        file_color = CYAN_F;
        special = true;
    }
    if (S_ISBLK(statbuf.st_mode)) {
        mode[0] = 'b';
        file_color = YELLOW_F;
        special = true;
    }
    if (S_ISCHR(statbuf.st_mode)) {
        mode[0] = 'c';
        file_color = YELLOW_F;
        special = true;
    }
	
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
        "%s%s"" ""%s% 2ld"" ""%s% 4d % 4d"" ""%s% 9ld%s"" ""%s%s"" ""%s%s%s""%c\n"
        , (color) ? RGB_B(40, 40, 40) RGB_F(255, 89, 94) : ""
        , mode
        , (color) ? RGB_F(255, 146, 76) : ""
        , statbuf.st_nlink
        , (color) ? RGB_F(255, 202, 58) : ""
        , statbuf.st_uid, statbuf.st_gid
        , (color) ? RGB_F(138, 201, 38) : ""
        , statbuf.st_size
        , (color) ? RGB_F(25, 130, 196) : ""
        , time
        , (color) ? DEFAULT_B RGB_F(40, 40, 40) "\u258C" BRIGHT : ""
        , (color) ? ((special) ? file_color : (executable ? GREEN_F : WHITE_F)) : ""
        , file
        , (color) ? RESET : ""
        , (special) ? (isdir ? '/' : ' ') : (executable ? '*' : ' ')
    );

    return buf;
}