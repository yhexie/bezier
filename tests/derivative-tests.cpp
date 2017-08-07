/*
 * Copyright © 2017 Oystein Myrmo
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting documentation, and
 * that the name of the copyright holders not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */
#include "bezier.h"
#include "assert.h"
#include "test_beziers.h"

void derivatives_tests()
{
    Bezier::Bezier<3> bezier3 = TestBeziers::Default::CubicBezier;
    Bezier::Bezier<2> bezier2 = bezier3.derivative();
    Bezier::Bezier<1> bezier1 = bezier2.derivative();
    Bezier::Bezier<0> bezier0 = bezier1.derivative();

    assert(bezier3.size() == 4);
    assert(bezier2.size() == 3);
    assert(bezier1.size() == 2);
    assert(bezier0.size() == 1);

    FUZZY_ASSERT_POINT(bezier2[0], -255, 120);
    FUZZY_ASSERT_POINT(bezier2[1], 555, 180);
    FUZZY_ASSERT_POINT(bezier2[2], 0, -660);

    FUZZY_ASSERT_POINT(bezier1[0], 1620, 120);
    FUZZY_ASSERT_POINT(bezier1[1], -1110, -1680);

    FUZZY_ASSERT_POINT(bezier0[0], -2730, -1800);

    bezier2 = TestBeziers::Default::QuadraticBezier;
    bezier1 = bezier2.derivative();
    bezier0 = bezier1.derivative();

    assert(bezier2.size() == 3);
    assert(bezier1.size() == 2);
    assert(bezier0.size() == 1);

    FUZZY_ASSERT_POINT(bezier1[0], -100, -90);
    FUZZY_ASSERT_POINT(bezier1[1], 160, -70);

    FUZZY_ASSERT_POINT(bezier0[0], 260, 20);
}

void extreme_values_tests()
{
    Bezier::Bezier<3> bezier3 = TestBeziers::Default::CubicBezier;

    Bezier::ExtremeValues xVals = bezier3.derivativeZero();
    BEZIER_ASSERT(xVals.size() == 3);
    FUZZY_ASSERT(xVals[0].t, 0.186811984);
    FUZZY_ASSERT(xVals[1].t, 1.0);
    FUZZY_ASSERT(xVals[2].t, 0.437850952);

    Bezier::ExtremePoints xPoints = bezier3.extremePoints();
    BEZIER_ASSERT(xPoints.size() == 4);
    FUZZY_ASSERT_POINT(xPoints[0], 97.6645355, 182.555511);
    FUZZY_ASSERT_POINT(xPoints[1], 220.0, 40.0);
    FUZZY_ASSERT_POINT(xPoints[2], 125.442337, 198.86235);
    FUZZY_ASSERT_POINT(xPoints[3], 120.0, 160.0);

    Bezier::AABB aabb = bezier3.aabb();
    BEZIER_ASSERT(aabb.size() == 4);
    FUZZY_ASSERT(aabb.minX(), 97.6645355);
    FUZZY_ASSERT(aabb.maxX(), 220.0);
    FUZZY_ASSERT(aabb.minY(), 40.0);
    FUZZY_ASSERT(aabb.maxY(), 198.86235);
    FUZZY_ASSERT(aabb.width(), 122.335464);
    FUZZY_ASSERT(aabb.height(), 158.86235);
    FUZZY_ASSERT(aabb.area(), 19434.5);

    Bezier::Bezier<2> bezier2 = TestBeziers::Default::QuadraticBezier;

    xVals = bezier2.derivativeZero();
    BEZIER_ASSERT(xVals.size() == 1);
    FUZZY_ASSERT(xVals[0].t, 0.384615391);

    xPoints = bezier2.extremePoints();
    BEZIER_ASSERT(xPoints.size() == 3);
    FUZZY_ASSERT_POINT(xPoints[0], 50.7692261, 121.863899);
    FUZZY_ASSERT_POINT(xPoints[1], 70.0, 155.0);
    FUZZY_ASSERT_POINT(xPoints[2], 100.0, 75.0);

    aabb = bezier2.aabb(xPoints);
    BEZIER_ASSERT(aabb.size() == 4);
    FUZZY_ASSERT(aabb.minX(), 50.7692261);
    FUZZY_ASSERT(aabb.maxX(), 100.0);
    FUZZY_ASSERT(aabb.minY(), 75.0);
    FUZZY_ASSERT(aabb.maxY(), 155.0);
    FUZZY_ASSERT(aabb.width(), 49.2307739);
    FUZZY_ASSERT(aabb.height(), 80.0);
    FUZZY_ASSERT(aabb.area(), 3938.46191);
}

int main()
{
    derivatives_tests();
    extreme_values_tests();

    return 0;
}