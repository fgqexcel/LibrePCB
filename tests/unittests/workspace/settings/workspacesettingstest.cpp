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
#include <librepcb/common/fileio/fileutils.h>
#include <librepcb/workspace/settings/workspacesettings.h>

#include <QtCore>

/*******************************************************************************
 *  Namespace
 ******************************************************************************/
namespace librepcb {
namespace workspace {
namespace tests {

/*******************************************************************************
 *  Test Class
 ******************************************************************************/

class WorkspaceSettingsTest : public ::testing::Test {};

/*******************************************************************************
 *  Test Methods
 ******************************************************************************/

TEST_F(WorkspaceSettingsTest, testStoreAndLoad) {
  FilePath fp = FilePath::getRandomTempPath().getPathTo("test.lp");

  // Store
  WorkspaceSettings obj1(fp);
  obj1.userName.set("foo bar");
  obj1.applicationLocale.set("de_CH");
  obj1.defaultLengthUnit.set(LengthUnit::nanometers());
  obj1.projectAutosaveIntervalSeconds.set(1234);
  obj1.useOpenGl.set(!obj1.useOpenGl.get());
  obj1.libraryLocaleOrder.set({"de_CH", "en_US"});
  obj1.libraryNormOrder.set({"foo", "bar"});
  obj1.repositoryUrls.set({QUrl("https://foo"), QUrl("https://bar")});
  obj1.useCustomPdfReader.set(obj1.useCustomPdfReader.get());
  obj1.pdfReaderCommand.set("my reader");
  obj1.pdfOpenBehavior.set(WorkspaceSettings::PdfOpenBehavior::NEVER);
  obj1.saveToFile();

  // Load
  WorkspaceSettings obj2(fp);
  EXPECT_EQ(obj1.userName.get().toStdString(),
            obj2.userName.get().toStdString());
  EXPECT_EQ(obj1.applicationLocale.get().toStdString(),
            obj2.applicationLocale.get().toStdString());
  EXPECT_EQ(obj1.defaultLengthUnit.get(), obj2.defaultLengthUnit.get());
  EXPECT_EQ(obj1.projectAutosaveIntervalSeconds.get(),
            obj2.projectAutosaveIntervalSeconds.get());
  EXPECT_EQ(obj1.useOpenGl.get(), obj2.useOpenGl.get());
  EXPECT_EQ(obj1.libraryLocaleOrder.get(), obj2.libraryLocaleOrder.get());
  EXPECT_EQ(obj1.libraryNormOrder.get(), obj2.libraryNormOrder.get());
  EXPECT_EQ(obj1.repositoryUrls.get(), obj2.repositoryUrls.get());
  EXPECT_EQ(obj1.useCustomPdfReader.get(), obj2.useCustomPdfReader.get());
  EXPECT_EQ(obj1.pdfReaderCommand.get(), obj2.pdfReaderCommand.get());
  EXPECT_EQ(obj1.pdfOpenBehavior.get(), obj2.pdfOpenBehavior.get());

  // Check if serialization of loaded settings leads to same file content
  SExpression sexpr1 = obj1.serializeToDomElement("settings");
  SExpression sexpr2 = obj2.serializeToDomElement("settings");
  EXPECT_EQ(sexpr1.toByteArray(), sexpr2.toByteArray());
}

/*******************************************************************************
 *  End of File
 ******************************************************************************/

}  // namespace tests
}  // namespace workspace
}  // namespace librepcb
