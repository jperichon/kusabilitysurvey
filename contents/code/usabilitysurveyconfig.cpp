/*
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

#include "usabilitysurveyconfig.h"

#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QVariant>

#include <Plasma/CheckBox>

#include <KDE/KSharedConfig>
#include <KDE/KConfigGroup>
#include <KDE/KComponentData>

static const QString CONFIG_GROUP_GENERAL = QString("General");
static const QString CONFIG_GROUP_APPLICATIONS = QString("Applications");

class UsabilitySurveyConfig::Private
{
public:
    KSharedConfig::Ptr m_config;
    QMap<QString, Plasma::CheckBox*> m_applications;
};

UsabilitySurveyConfig::UsabilitySurveyConfig()
    : d_ptr(new Private)
{
    KComponentData componentData(QByteArray("usabilitysurvey"));
    d_ptr->m_config = KSharedConfig::openConfig(componentData);
}

void UsabilitySurveyConfig::init()
{
    KConfigGroup cg(d_ptr->m_config, CONFIG_GROUP_APPLICATIONS);
    QMapIterator<QString, QString> i(cg.entryMap());
    while(i.hasNext()) {
        i.next();
        bool enabled = QVariant(i.value()).toBool();
        Plasma::CheckBox* cb = new Plasma::CheckBox;
        cb->setChecked(enabled);
        d_ptr->m_applications.insert(i.key(), cb);
    }
}

bool UsabilitySurveyConfig::isEnabled(const QString& appName) const
{
    KConfigGroup cg(d_ptr->m_config, CONFIG_GROUP_APPLICATIONS);
    QVariant res = cg.readEntry(appName, true);
    return res.toBool();
}

void UsabilitySurveyConfig::surveyCreated(const QString& appName)
{
    if(d_ptr->m_applications.contains(appName)) {
        // new application
    }
    if(isEnabled(appName)) {
    }
}

void UsabilitySurveyConfig::updateEntries() const
{
    KConfigGroup cg(d_ptr->m_config, CONFIG_GROUP_APPLICATIONS);
    QMapIterator<QString, Plasma::CheckBox*> i(d_ptr->m_applications);
    while(i.hasNext()) {
        i.next();
        bool enabled = i.value()->isChecked();
        cg.writeEntry(i.key(), enabled);
    }
}
