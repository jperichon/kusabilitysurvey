set(testParser_SRCS
    testparser.cpp

    ../surveybuilder.cpp
    ../surveyhandler.cpp
    ../survey.cpp
    ../surveygrammar.cpp

    ../usabilitysurveyconfig.cpp

    ../questions/openquestion.cpp
    ../questions/gridquestion.cpp
    ../questions/gridquestion_p.h
    ../questions/scalequestion.cpp
    ../questions/buttonquestion.cpp
    ../questions/comboboxquestion.cpp
    ../questions/radiobuttonquestion.cpp
    ../questions/question.cpp
    ../questions/closedquestion.cpp
    ../questions/closedquestion_p.h
    ../questions/simpleclosedquestion.cpp
    ../questions/simpleclosedquestion_p.h
    ../questions/checkboxquestion.cpp
)

remove_definitions(-DQT_NO_STL)

kde4_add_unit_test(testParser
    ${testParser_SRCS}
)

target_link_libraries(testParser
    ${KDE4_KDECORE_LIBS}
    ${QT_QTTEST_LIBRARY}
    ${KDE4_PLASMA_LIBS}
    ${KDE4_KDEUI_LIBS}
    ${KDE4_KUTILS_LIBS}
)
