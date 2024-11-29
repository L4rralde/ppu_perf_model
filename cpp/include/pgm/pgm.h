#ifndef PGM_H
#define PGM_H

#include <string>
#include <vector>

typedef std::vector< std::vector<unsigned char> > Img;

Img read_pgm(std::string& fpath);
void print(Img&& img);


#endif