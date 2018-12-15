#include <iostream>
#include "../math/Matrix4D.h"
#include "../math/Vector3D.h"
using namespace Math;
double radian(float degrees)
{
    return degrees * 0.01745329251994329576923690768489;
}
void print(Matrix4D matrix) {

    for(int i = 0; i < 16; i++) {
        if(i % 4 == 0)
            std::cout << std::endl;
        std::cout << matrix[i] << ",";
    }
    std::cout << std::endl;
}
int main() {

    Matrix4D matrix_identity = Matrix4D::makeIdentity();
    print(matrix_identity);

    Matrix4D matrix_rotation = Matrix4D::makeRotationX(radian(30));
    print(matrix_rotation);

    Matrix4D matrix_translation = Matrix4D::makeTranslation(10, 10, 10);
    print(matrix_translation);

    Matrix4D matrix_lookat = Matrix4D::lookAt(
        Vector3D(0.0, 3.0, 4.0), Vector3D(), Vector3D(0.0, 1.0, 0.0)
    );
    print(matrix_lookat);

    Matrix4D matrix_perspective = Matrix4D::makePerspective(
        radian(70), 0.47927, 1, 1000
    );
    print(matrix_perspective);
    
    Matrix4D perspective_inverse = matrix_perspective.getInverse();
    print(perspective_inverse);
    return 0;
}
