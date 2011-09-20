/*
 * Survey Handler
 *
 * Copyright 2011 Jonathan Perichon <jonathan.perichon@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License or (at your option) version 3 or any later version
 * accepted by the membership of KDE e.V. (or its successor approved
 * by the membership of KDE e.V.), which shall act as a proxy
 * defined in Section 14 of version 3 of the license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "surveyhandler.h"

#include <QtCore/QString>

#include <Plasma/DataEngineManager>
#include <Plasma/Service>
#include <Plasma/ServiceJob>

#include "survey.h"
#include "surveybuilder.h"

static const char engineName[] = "surveys";

SurveyHandler::SurveyHandler(QObject* parent)
    : QObject(parent),
      m_engine(0)
{
}

void SurveyHandler::init()
{
    kDebug() << "initializing engine";
    m_engine = Plasma::DataEngineManager::self()->loadEngine(engineName);

    if(!m_engine->isValid()) {
        kDebug() << "could not initialize engine";
        m_engine = 0;
        Plasma::DataEngineManager::self()->unloadEngine(engineName);
        return;
    }

    m_engine->connectAllSources(this);
    connect(m_engine, SIGNAL(sourceAdded(const QString&)),
            this, SLOT(prepareNotification(const QString&)));
    connect(m_engine, SIGNAL(sourceRemoved(const QString&)),
            this, SLOT(teardownSurvey(const QString&)));
}

SurveyHandler::~SurveyHandler()
{
    if(m_engine) {
        Plasma::DataEngineManager::self()->unloadEngine(engineName);
    }
}

void SurveyHandler::prepareSurvey(const QString& source)
{
    kDebug() << "prepping new survey";
    if(m_engine) {
        kDebug() << "new source is" << source;
        m_engine->connectSource(source, this);
    }

}

void SurveyHandler::dataUpdated(const QString& source,
                                const Plasma::DataEngine::Data& data)
{
    Survey* survey;
    QString appName = data.value("appName").toString(); // required to accept multiples survey for the same application
    SurveyBuilder::buildSurvey(data.value("path").toString(), survey);
    survey->setParent(this);

    m_surveys[source] = survey;

    kDebug() << "emitting surveyCreated";
    emit surveyCreated(survey);
}

void SurveyHandler::teardownSurvey(const QString& source)
{
    if(m_surveys.contains(source)) {
        kDebug() << "removing source" << source;
        m_surveys.remove(source);
    }
}

#include "surveyhandler.moc"
