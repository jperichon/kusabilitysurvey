add_subdirectory(tests)

remove_definitions(-DQT_NO_STL)

set(UsabilitySurvey_SRCS
    surveybuilder.cpp
    surveyhandler.cpp
    survey.cpp
    surveygrammar.cpp

    usabilitysurveyconfig.cpp

    questions/openquestion.cpp
    questions/gridquestion.cpp
    questions/gridquestion_p.h
    questions/scalequestion.cpp
    questions/buttonquestion.cpp
    questions/comboboxquestion.cpp
    questions/radiobuttonquestion.cpp
    questions/question.cpp
    questions/closedquestion.cpp
    questions/closedquestion_p.h
    questions/simpleclosedquestion.cpp
    questions/simpleclosedquestion_p.h
    questions/checkboxquestion.cpp
)

kde4_add_plugin(UsabilitySurvey
    ${UsabilitySurvey_SRCS}
)

target_link_libraries(UsabilitySurvey
    ${KDE4_PLASMA_LIBS}
    ${KDE4_KDEUI_LIBS}
    ${KDE4_KUTILS_LIBS}
)

