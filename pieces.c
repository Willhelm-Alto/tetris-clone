struct piece_s{int width; int vertices[4][2]; };
typedef struct piece_s Piece;

Piece J = {
  2,
  {
    {1, 0},
    {1, 1},
    {1, 2},
    {0, 2},     
  }
};

Piece L = {
  2,
  {
    {0, 0},
    {0, 1},
    {0, 2},
    {1, 2},
  }
};

Piece Z = {
  3,
  {
    {0, 0},
    {1, 0},
    {1, 1},
    {2, 1}
  }
};

Piece S = {
  3,
  {
    {0, 1},
    {1, 1},
    {1, 0},
    {2, 0}
  }
};

Piece I = {
  1,
  {
    {0, 0},
    {0, 1},
    {0, 2},
    {0, 3},
  }
};

Piece O = {
  2,
  {
    {0, 0},
    {1, 0},
    {0, 1},
    {1, 1},
  }
};

Piece T = {
  3,
  {
    {0, 0},
    {1, 0},
    {2, 0},
    {1, 1},
  }
};


// #define J J;
// #define L L;
// #define Z Z;
// #define S S;
// #define I I;
// #define O O;
// #define T T;
