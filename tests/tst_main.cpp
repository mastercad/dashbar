#include <QtTest>

// Testing classes
#include "tst_windowPositionManager.h"
#include "tst_buttonManager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    int status = 0;
    QTest::setMainSourcePath(__FILE__, QT_TESTCASE_BUILDDIR);
    {
        TestWindowPositionManager testWindowPositionManager;
        status |= QTest::qExec(&testWindowPositionManager, argc, argv);
    }
    {
        TestButtonManager testButtonManager;
        status |= QTest::qExec(&testButtonManager, argc, argv);
    }
    return status;
}

//QTEST_MAIN(TestMain)
