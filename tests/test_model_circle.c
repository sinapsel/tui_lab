#include <testing.h>
#include <assertions.h>
#include "models/shape.h"
#include "models/circle.h"

#include "mocks/canvas.h"

TEST(circle_negative_values) {
    #pragma region arrange
    Shape* r = shape_create_circle(-5.0);
    #pragma endregion arrange


    #pragma region act
    double _area = area(r);
    #pragma endregion act


    #pragma region assert
    ASSERT( _area == -1.0);
    #pragma endregion assert

    destroy(r);
}

TEST(circle_positive_values) {
    #pragma region arrange
    Shape* r = shape_create_circle(4.0);
    #pragma endregion arrange

    #pragma region act
    double _area = area(r);
    #pragma endregion act

    #pragma region assert
    ASSERT_EQ_EPS(_area, 4.0 * 4.0 * 3.1415, 1e-2);
    #pragma endregion assert

    destroy(r);
}
