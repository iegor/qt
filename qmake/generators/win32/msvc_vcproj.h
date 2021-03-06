
/****************************************************************************
**
** Definition of VcprojGenerator class.
**
** Copyright (C) 1992-2008 Trolltech ASA.  All rights reserved.
**
** This file is part of qmake.
**
** This file may be used under the terms of the GNU General
** Public License versions 2.0 or 3.0 as published by the Free
** Software Foundation and appearing in the files LICENSE.GPL2
** and LICENSE.GPL3 included in the packaging of this file.
** Alternatively you may (at your option) use any later version
** of the GNU General Public License if such license has been
** publicly approved by Trolltech ASA (or its successors, if any)
** and the KDE Free Qt Foundation.
**
** Please review the following information to ensure GNU General
** Public Licensing requirements will be met:
** http://trolltech.com/products/qt/licenses/licensing/opensource/.
** If you are unsure which license is appropriate for your use, please
** review the following information:
** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
** or contact the sales department at sales@trolltech.com.
**
** This file may be used under the terms of the Q Public License as
** defined by Trolltech ASA and appearing in the file LICENSE.QPL
** included in the packaging of this file.  Licensees holding valid Qt
** Commercial licenses may use this file in accordance with the Qt
** Commercial License Agreement provided with the Software.
**
** This file is provided "AS IS" with NO WARRANTY OF ANY KIND,
** INCLUDING THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE. Trolltech reserves all rights not granted
** herein.
**
**********************************************************************/

#ifndef __MSVC_VCPROJ_H__
#define __MSVC_VCPROJ_H__

#include "winmakefile.h"
#include "msvc_objectmodel.h"

enum target {
    Application,
    SharedLib,
    StaticLib
};

struct QUuid;
class VcprojGenerator : public Win32MakefileGenerator
{
    bool init_flag;
    bool writeVcprojParts(QTextStream &);

    bool writeMakefile(QTextStream &);
    virtual void writeSubDirs(QTextStream &t);
    QString findTemplate(QString file);
    void init();

public:
    VcprojGenerator(QMakeProject *p);
    ~VcprojGenerator();

    QString defaultMakefile() const;
    virtual bool doDepends() const { return FALSE; } //never necesary
    QString precompH, precompHFilename,
	    precompObj, precompPch;
    bool usePCH;

protected:
    virtual bool openOutput(QFile &file) const;
    virtual void processPrlVariable(const QString &, const QStringList &);
    virtual bool findLibraries();
    virtual void outputVariables();
    QString fixFilename(QString ofile) const;
    
    void initOld();
    void initProject();
    void initConfiguration();
    void initCompilerTool();
    void initLinkerTool();
    void initLibrarianTool();
    void initIDLTool();
    void initCustomBuildTool();
    void initPreBuildEventTools();
    void initPostBuildEventTools();
    void initPreLinkEventTools();
    void initSourceFiles();
    void initHeaderFiles();
    void initMOCFiles();
    void initUICFiles();
    void initFormsFiles();
    void initTranslationFiles();
    void initLexYaccFiles();
    void initResourceFiles();

    VCProject vcProject;
    target projectTarget;

private:
    QUuid getProjectUUID(const QString &filename=QString::null);
    QUuid increaseUUID(const QUuid &id);
    friend class VCFilter;
};

inline VcprojGenerator::~VcprojGenerator()
{ }

inline QString VcprojGenerator::defaultMakefile() const
{
    return project->first("TARGET") + project->first("VCPROJ_EXTENSION");
}

inline bool VcprojGenerator::findLibraries()
{ 
    return Win32MakefileGenerator::findLibraries("MSVCVCPROJ_LIBS");
}

#endif /* __MSVC_VCPROJ_H__ */
