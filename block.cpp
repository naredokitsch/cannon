#include <vector>
#include <map>

using namespace std;

vector<vector<float> > vertex_block {{1 , -1 , -1} , {1 , -1 , 1} , {-1 , -1 , 1} , {-1 , -1 , -1} , {1 , 1 , -1} , {1 , 1 , 1} , {-1 , 1 , 1} , {-1 , 1 , -1}};
vector<vector<float> > texts_block {{0.666413 , 0.250594} , {0.333587 , 0.250594} , {0.333587 , 0.000975} , {0.666413 , 0.000975} , {0.666413 , 0.500213} , {0.666413 , 0.749833} , {0.333587 , 0.749833} , {0.333587 , 0.500214} , {0.000761 , 0.500214} , {0.000761 , 0.749833} , {0.333587 , 0.999452} , {0.666413 , 0.999452} , {0.999239 , 0.500213} , {0.999239 , 0.749833}};
vector<vector<float> > normals_block {{0.0000 , -1.0000 , 0.0000} , {0.0000 , 1.0000 , 0.0000} , {1.0000 , 0.0000 , 0.0000} , {0.0000 , 0.0000 , 1.0000} , {-1.0000 , 0.0000 , 0.0000} , {0.0000 , 0.0000 , -1.0000}};
vector<vector<vector<int> > > quads_block {{{0,0,0},{1,1,0},{2,2,0},{3,3,0}},{{4,4,1},{7,5,1},{6,6,1},{5,7,1}},{{0,0,2},{4,4,2},{5,7,2},{1,1,2}},{{1,8,3},{5,7,3},{6,6,3},{2,9,3}},{{2,10,4},{6,6,4},{7,5,4},{3,11,4}},{{4,4,5},{0,12,5},{3,13,5},{7,5,5}}};
vector<vector<vector<int> > > trng_block {{}};
vector<vector<vector<int> > > poly_block {{}};

map<string,vector<vector<float> > > geo_block = {{"vertex", vertex_block},{"texts", texts_block},{"normals", normals_block}};
map<string,vector<vector<vector<int> > > > faces_block = {{"quads", quads_block},{"trng", trng_block},{"poly", poly_block}};
