/*
 * LibrePCB - Professional EDA for everyone!
 * Copyright (C) 2013 LibrePCB Developers, see AUTHORS.md for contributors.
 * https://librepcb.org/
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*******************************************************************************
 *  Includes
 ******************************************************************************/

#include <gtest/gtest.h>
#include <librepcb/common/geometry/stroketext.h>

/*******************************************************************************
 *  Namespace
 ******************************************************************************/
namespace librepcb {
namespace tests {

/*******************************************************************************
 *  Test Class
 ******************************************************************************/

class StrokeTextTest : public ::testing::Test {};

/*******************************************************************************
 *  Test Methods
 ******************************************************************************/

TEST_F(StrokeTextTest, testSerializeAndDeserialize) {
  StrokeText obj1(Uuid::createRandom(), GraphicsLayerName("foo"), "hello world",
                  Point(12, 34), Angle(56), PositiveLength(123),
                  UnsignedLength(456), StrokeTextSpacing(),
                  StrokeTextSpacing(Ratio(1234)),
                  Alignment(HAlign::right(), VAlign::center()), true, false);
  SExpression sexpr1 = obj1.serializeToDomElement("text");

  StrokeText obj2(sexpr1);
  SExpression sexpr2 = obj2.serializeToDomElement("text");

  EXPECT_EQ(sexpr1.toByteArray(), sexpr2.toByteArray());
}

/*******************************************************************************
 *  End of File
 ******************************************************************************/

}  // namespace tests
}  // namespace librepcb
