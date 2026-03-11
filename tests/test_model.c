#include <testing.h>
#include <assertions.h>
#include "models/shape.h"

#include "mocks/canvas.h"

TEST(rectangle_negative_values) {
    #pragma region arrange
    Shape* r = shape_create_rectangle(-5.0, 10.0);
    #pragma endregion arrange


    #pragma region act
    double _area = area(r);
    #pragma endregion act


    #pragma region assert
    EXPECT_ABORTED();
    #pragma endregion assert

    destroy(r);
}

TEST(rectangle_positive_values) {
    #pragma region arrange
    Shape* r = shape_create_rectangle(4.0, 5.0);
    #pragma endregion arrange

    #pragma region act
    double _area = area(r);
    #pragma endregion act

    #pragma region assert
    ASSERT(_area == 20.0);
    #pragma endregion assert

    destroy(r);
}

TEST (rectangle_draw_invalid) {
    #pragma region arrange
    Shape* r = shape_create_rectangle(-4.0,-5.0);
    #pragma endregion arrange

    #pragma region act
    MockedCanvas c = {};
    draw(r, (Canvas*)&c, 0, 0);
    #pragma endregion act

    #pragma region assert
    ASSERT_STR_EQ(c.drawed_text, "Invalid size");
    #pragma endregion assert

    destroy(r);
}