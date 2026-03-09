#include "testing.h"
#include "assertions.h"
#include "models/shape.h"
#include "models/circle.h"

TEST(test_rectangle_negative_values) {
    // arrange
    Shape* r = shape_create_rectangle(-5.0, 10.0);
    // act
    double _area = area(r);
    // assert
    double expected = -1.0;
    assert(_area == expected);
    destroy(r);
}

TEST(test_rectangle_positive_values) {

    // Arrange

    Shape* r = shape_create_rectangle(4.0, 5.0);

    // Act 
    double _area = area(r);

    // Assert
    assert(_area == 20.0);
    destroy(r);
}
