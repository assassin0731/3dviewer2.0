#include <gtest/gtest.h>

#include "Model/facade.h"

constexpr double kEps = 0.000001;

TEST(Test, parser_test1) {
  const char *path = "Models/file.obj";
  Facade facade;
  facade.ParseObjFile(path);
  int real_index[48] = {1, 2, 2, 3, 3, 1, 3, 2, 2, 4, 4, 3, 3, 4, 4, 5,
                        5, 3, 5, 4, 4, 6, 6, 5, 5, 6, 6, 7, 7, 5, 7, 6,
                        6, 8, 8, 7, 7, 8, 8, 1, 1, 7, 1, 8, 8, 2, 2, 1};
  double real_vertex[24] = {
      -0.500000, -0.500000, 0.500000,  0.500000, -0.500000, 0.500000,
      -0.500000, 0.500000,  0.500000,  0.500000, 0.500000,  0.500000,
      -0.500000, 0.500000,  -0.500000, 0.500000, 0.500000,  -0.500000,
      -0.500000, -0.500000, -0.500000, 0.500000, -0.500000, -0.500000};
  EXPECT_EQ(8, facade.get_elements()->vertex.size()/3);
  EXPECT_EQ(36, facade.get_elements()->index.size()/2);
  for (int i = 0; i < 48; ++i) {
    EXPECT_EQ(real_index[i] - 1, facade.get_elements()->index[i]);
  }
  for (int i = 0; i < 24; ++i) {
    EXPECT_NEAR(real_vertex[i], facade.get_elements()->vertex[i], kEps);
  }
}

TEST(Test, parser_test2) {
  const char *path = "Models/fole1.obj";
  Facade facade;
  facade.ParseObjFile(path);
  int real_index[10] = {1, 2, 2, 3, 3, 4, 4, 1, 1, 5};
  double real_vertex[10] = {-0.500000, -0.500000, 0.500000, 0.500000, -0.500000,
                            0.500000,  -0.500000, 0.500000, 0.500000, 0.500000};
  EXPECT_EQ(8, facade.get_elements()->vertex.size()/3);
  EXPECT_EQ(16, facade.get_elements()->index.size()/2);
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(real_index[i] - 1, facade.get_elements()->index[i]);
  }
  for (int i = 0; i < 10; ++i) {
    EXPECT_NEAR(real_vertex[i], facade.get_elements()->vertex[i], kEps);
  }
}

TEST(Test, parser_test3) {
  const char *path = "Models/heart.obj";
  Facade facade;
  facade.ParseObjFile(path);
  int real_index[10] = {1, 2, 2, 3, 3, 4, 4, 1, 5, 6};
  double real_vertex[10] = {-5.7868, -2.8897, 6.9550,  -5.8939, -2.7443,
                            6.7745,  -5.4647, -2.7112, 6.3057,  -5.3747};
  EXPECT_EQ(5634, facade.get_elements()->vertex.size()/3);
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(real_index[i] - 1, facade.get_elements()->index[i]);
  }
  for (int i = 0; i < 10; ++i) {
    EXPECT_NEAR(real_vertex[i], facade.get_elements()->vertex[i], kEps);
  }
}

TEST(Test, parser_test4) {
  const char *path = "Models/luster.obj";
  Facade facade;
  facade.ParseObjFile(path);
  int real_index[10] = {1, 2, 2, 3, 3, 4, 4, 1, 2, 5};
  double real_vertex[10] = {-168.6158,  -9350.9287, 9.8047,    -167.7503,
                            -9350.9287, 15.2691,    -167.6017, -9344.4023,
                            15.2691,    -168.4663};
  EXPECT_EQ(59947, facade.get_elements()->vertex.size()/3);
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(real_index[i] - 1, facade.get_elements()->index[i]);
  }
  for (int i = 0; i < 10; ++i) {
    EXPECT_NEAR(real_vertex[i], facade.get_elements()->vertex[i], kEps);
  }
}

TEST(Test, scaling_test1) {
  const char *path = "Models/file.obj";
  Facade facade;
  facade.ParseObjFile(path);
  double real_vertex[24] = {
      -0.600000, -0.600000, 0.600000,  0.600000, -0.600000, 0.600000,
      -0.600000, 0.600000,  0.600000,  0.600000, 0.600000,  0.600000,
      -0.600000, 0.600000,  -0.600000, 0.600000, 0.600000,  -0.600000,
      -0.600000, -0.600000, -0.600000, 0.600000, -0.600000, -0.600000};
  facade.GeometryScale(1.2);
  for (int i = 0; i < 24; ++i) {
    EXPECT_NEAR(real_vertex[i], facade.get_elements()->vertex[i], kEps);
  }
}

TEST(Test, scaling_test2) {
  const char *path = "Models/file.obj";
  Facade facade;
  facade.ParseObjFile(path);
  double real_vertex[24] = {
      -0.400000, -0.400000, 0.400000,  0.400000, -0.400000, 0.400000,
      -0.40000,  0.40000,   0.40000,   0.40000,  0.400000,  0.400000,
      -0.40000,  0.400000,  -0.40000,  0.400000, 0.400000,  -0.400000,
      -0.400000, -0.40000,  -0.400000, 0.400000, -0.400000, -0.40000};
  facade.GeometryScale(0.8);
  for (int i = 0; i < 24; ++i) {
    EXPECT_NEAR(real_vertex[i], facade.get_elements()->vertex[i], kEps);
  }
}

TEST(Test, scaling_test3) {
  const char *path = "Models/file.obj";
  Facade facade;
  facade.ParseObjFile(path);
  double real_vertex[24] = {
      -0.28800000, -0.288, 0.288,  0.288,  -0.288, 0.288,  -0.288, 0.288,
      0.288,       0.288,  0.288,  0.288,  -0.288, 0.2880, -0.288, 0.2880,
      0.28800,     -0.288, -0.288, -0.288, -0.288, 0.288,  -0.288, -0.288};
  facade.GeometryScale(0.8);
  facade.GeometryScale(0.4);
  facade.GeometryScale(1.8);
  for (int i = 0; i < 24; ++i) {
    EXPECT_NEAR(real_vertex[i], facade.get_elements()->vertex[i], kEps);
  }
}

TEST(Test, moving_test1) {
  const char *path = "Models/file.obj";
  Facade facade;
  facade.ParseObjFile(path);
  double real_vertex[24] = {
      19.500000, -0.500000, 0.500000,  20.500000, -0.500000, 0.500000,
      19.50000,  0.50000,   0.50000,   20.50000,  0.500000,  0.500000,
      19.50000,  0.500000,  -0.50000,  20.500000, 0.500000,  -0.500000,
      19.500000, -0.50000,  -0.500000, 20.500000, -0.500000, -0.50000};
  facade.GeometryMove(20,0,0);
  for (int i = 0; i < 24; ++i) {
    EXPECT_NEAR(real_vertex[i], facade.get_elements()->vertex[i], kEps);
  }
}

TEST(Test, moving_test2) {
  const char *path = "Models/file.obj";
  Facade facade;
  facade.ParseObjFile(path);
  double real_vertex[24] = {
      -0.500000, -10.500000, 0.500000,  0.500000, -10.500000, 0.500000,
      -0.500000, -9.500000,  0.500000,  0.500000, -9.500000,  0.500000,
      -0.500000, -9.500000,  -0.500000, 0.500000, -9.500000,  -0.500000,
      -0.500000, -10.500000, -0.500000, 0.500000, -10.500000, -0.500000};
  facade.GeometryMove(0,-10,0);
  for (int i = 0; i < 24; ++i) {
    EXPECT_NEAR(real_vertex[i], facade.get_elements()->vertex[i], kEps);
  }
}

TEST(Test, moving_test3) {
  const char *path = "Models/file.obj";
  Facade facade;
  facade.ParseObjFile(path);
  double real_vertex[24] = {
      -0.500000, -0.500000, 0.500000,  0.500000, -0.500000, 0.500000,
      -0.500000, 0.500000,  0.500000,  0.500000, 0.500000,  0.500000,
      -0.500000, 0.500000,  -0.500000, 0.500000, 0.500000,  -0.500000,
      -0.500000, -0.500000, -0.500000, 0.500000, -0.500000, -0.500000};
  facade.GeometryMove(0,0,0);
  for (int i = 0; i < 24; ++i) {
    EXPECT_NEAR(real_vertex[i], facade.get_elements()->vertex[i], kEps);
  }
}

TEST(Test, moving_test4) {
  const char *path = "Models/file.obj";
  Facade facade;
  facade.ParseObjFile(path);
  double real_vertex[24] = {
      3.500000, 0.500000, -2.500000, 4.500000, 0.500000, -2.500000,
      3.500000, 1.500000, -2.500000, 4.500000, 1.500000, -2.500000,
      3.500000, 1.500000, -3.500000, 4.500000, 1.500000, -3.500000,
      3.500000, 0.500000, -3.500000, 4.500000, 0.500000, -3.500000};
  facade.GeometryMove(1, 2, 1);
  facade.GeometryMove(-2, 3, 2);
  facade.GeometryMove(5, -4, -6);
  for (int i = 0; i < 24; ++i) {
    EXPECT_NEAR(real_vertex[i], facade.get_elements()->vertex[i], kEps);
  }
}

TEST(Test, rotate_test1) {
  const char *path = "Models/file.obj";
  Facade facade;
  facade.ParseObjFile(path);
  double real_x = -0.762267;
  double real_y = 0.228705;
  double real_z = 0.34153;
  facade.GeometryRotate(30. / 57.3, 30. / 57.3, 30. / 57.3);
  EXPECT_NEAR(real_x, facade.get_elements()->vertex[0], kEps);
  EXPECT_NEAR(real_y, facade.get_elements()->vertex[1], kEps);
  EXPECT_NEAR(real_z, facade.get_elements()->vertex[2], kEps);
}

TEST(Test, undo_test1) {
  const char *path = "Models/file.obj";
  Facade facade;
  facade.ParseObjFile(path);
  double real_vertex[24] = {
      -0.500000, -0.500000, 0.500000,  0.500000, -0.500000, 0.500000,
      -0.500000, 0.500000,  0.500000,  0.500000, 0.500000,  0.500000,
      -0.500000, 0.500000,  -0.500000, 0.500000, 0.500000,  -0.500000,
      -0.500000, -0.500000, -0.500000, 0.500000, -0.500000, -0.500000};
  facade.GeometryRotate(30. / 57.3, 0, 0);
  facade.UndoPreviousChange();
  for (int i = 0; i < 24; ++i) {
    EXPECT_NEAR(real_vertex[i], facade.get_elements()->vertex[i], kEps);
  }
}

TEST(Test, undo_test2) {
  const char *path = "Models/file.obj";
  Facade facade;
  facade.ParseObjFile(path);
  double real_vertex[24] = {
      -0.500000, -0.500000, 0.500000,  0.500000, -0.500000, 0.500000,
      -0.500000, 0.500000,  0.500000,  0.500000, 0.500000,  0.500000,
      -0.500000, 0.500000,  -0.500000, 0.500000, 0.500000,  -0.500000,
      -0.500000, -0.500000, -0.500000, 0.500000, -0.500000, -0.500000};
  facade.GeometryRotate(0, 30. / 57.3, 0);
  facade.UndoPreviousChange();
  for (int i = 0; i < 24; ++i) {
    EXPECT_NEAR(real_vertex[i], facade.get_elements()->vertex[i], kEps);
  }
}

TEST(Test, undo_test3) {
  const char *path = "Models/file.obj";
  Facade facade;
  facade.ParseObjFile(path);
  double real_vertex[24] = {
      -0.500000, -0.500000, 0.500000,  0.500000, -0.500000, 0.500000,
      -0.500000, 0.500000,  0.500000,  0.500000, 0.500000,  0.500000,
      -0.500000, 0.500000,  -0.500000, 0.500000, 0.500000,  -0.500000,
      -0.500000, -0.500000, -0.500000, 0.500000, -0.500000, -0.500000};
  facade.GeometryRotate(0, 30. / 57.3, 0);
  facade.GeometryScale(1.1);
  facade.GeometryMove(10,10,10);
  facade.UndoPreviousChange();
  facade.UndoPreviousChange();
  facade.UndoPreviousChange();
  for (int i = 0; i < 24; ++i) {
    EXPECT_NEAR(real_vertex[i], facade.get_elements()->vertex[i], kEps);
  }
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}