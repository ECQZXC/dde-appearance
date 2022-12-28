/*
 * Copyright (C) 2021 ~ 2023 Deepin Technology Co., Ltd.
 *
 * Author:     caixiangrong <caixiangrong@uniontech.com>
 *
 * Maintainer: caixiangrong <caixiangrong@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef APPEARANCEDBUSPROXY_H
#define APPEARANCEDBUSPROXY_H

#include "dccdbusinterface.h"
#include "scaleFactors.h"

#include <QSharedPointer>

class AppearanceDBusProxy : public QObject
{
    Q_OBJECT
public:
    explicit AppearanceDBusProxy(QObject *parent = nullptr);
    void setUserInterface(const QString &userPath);
    // Notifications
public Q_SLOTS:
    void Notify(const QString &in0, const QString &in2, const QString &summary, const QString &body, const QStringList &options, const QVariantMap &optionMap, int expireTimeout);
private Q_SLOTS:
    void NotifyNid(uint id);

    // wmInterface
public:
    Q_PROPERTY(QString cursorTheme READ cursorTheme WRITE setcursorTheme NOTIFY cursorThemeChanged)
    QString cursorTheme();
    void setcursorTheme(const QString &cursorTheme);

public Q_SLOTS:
    int WorkspaceCount();
    QString GetWorkspaceBackgroundForMonitor(int index, const QString &strMonitorName);
    void SetCurrentWorkspaceBackgroundForMonitor(const QString &uri, const QString &strMonitorName);
    void SetDecorationDeepinTheme(const QString &deepinThemeName);
    void ChangeCurrentWorkspaceBackground(const QString &uri);
    int GetCurrentWorkspace();
    void SetWorkspaceBackgroundForMonitor(int index, const QString &strMonitorName, const QString &uri);

Q_SIGNALS:
    void workspaceCountChanged(int count);
    void WorkspaceSwitched(int from, int to);
    void cursorThemeChanged(const QString &cursorTheme);

    // displayInterface
public:
    Q_PROPERTY(QString Primary READ primary NOTIFY PrimaryChanged)
    QString primary();
    Q_PROPERTY(QList<QDBusObjectPath> Monitors READ monitors NOTIFY MonitorsChanged)
    QList<QDBusObjectPath> monitors();

public Q_SLOTS:
    QStringList ListOutputNames();

Q_SIGNALS:
    void PrimaryChanged(const QString &Primary);
    void MonitorsChanged(QList<QDBusObjectPath> monitors);

    // xSettingsInterface
public Q_SLOTS:
    void SetString(const QString &prop, const QString &v);
    double GetScaleFactor();
    void SetScaleFactor(double scale);
    ScaleFactors GetScreenScaleFactors();
    void SetScreenScaleFactors(const ScaleFactors &factors);

Q_SIGNALS:
    void SetScaleFactorStarted();
    void SetScaleFactorDone();

    // accountInter
public Q_SLOTS:
    static QString FindUserById(const QString &uid);

    // userInterface
public:
    Q_PROPERTY(QStringList DesktopBackgrounds READ desktopBackgrounds NOTIFY DesktopBackgroundsChanged)
    QStringList desktopBackgrounds();
    Q_PROPERTY(QString GreeterBackground READ greeterBackground NOTIFY GreeterBackgroundChanged)
    QString greeterBackground();

public Q_SLOTS:
    void SetCurrentWorkspace(int currentWorkspace);
    void SetDesktopBackgrounds(const QStringList &val);
    void SetGreeterBackground(const QString &bg);
Q_SIGNALS:
    void DesktopBackgroundsChanged(const QStringList &desktopBackgrounds);
    void GreeterBackgroundChanged(const QString &greeterBackground);
    // timeDateInterface
public:
    Q_PROPERTY(QString Timezone READ timezone NOTIFY TimezoneChanged)
    QString timezone();
    Q_PROPERTY(bool NTP READ nTP NOTIFY NTPChanged)
    bool nTP();

Q_SIGNALS:
    void TimezoneChanged(QString timezone);
    void NTPChanged(bool NTP);

    // sessionTimeDateInterface
public:
    Q_PROPERTY(bool NTPSession READ nTPSession NOTIFY NTPSessionChanged)
    bool nTPSession();

Q_SIGNALS:
    void TimeUpdate();
    void NTPSessionChanged();

    // imageBlurInterface
public:
    static void Delete(const QString &file);
    static QString Get(const QString &file);

    // imageEffectInterface
public:
    static void Delete(const QString &effect, const QString &filename);
    static QString Get(const QString &effect, const QString &filename);

    // Daemon
public:
    static void DeleteCustomWallPaper(const QString &username, const QString &file);
    static QStringList GetCustomWallPapers(const QString &username);
    static QString SaveCustomWallPaper(const QString &username, const QString &file);

Q_SIGNALS:
    void HandleForSleep(bool sleep);

private:
    DCCDBusInterface *m_wmInterface;
    DCCDBusInterface *m_displayInterface;
    DCCDBusInterface *m_xSettingsInterface;
    DCCDBusInterface *m_timeDateInterface;
    DCCDBusInterface *m_sessionTimeDateInterface;
    QSharedPointer<DCCDBusInterface> m_userInterface;
    uint m_nid;
};

#endif // APPEARANCEDBUSPROXY_H
