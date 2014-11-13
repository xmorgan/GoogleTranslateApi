#include "gtapitranslation.h"

#include <QDebug>

GTApiTranslation::GTApiTranslation(const GTReplyObject & gtReplyObject)
    : root(gtReplyObject)
{

}

QStringList GTApiTranslation::translation() const
{
    QStringList res;    

    foreach( const GTReplyObject &sentence, root[0] ){
        res << sentence[0].toString();
    }

    if (!res.isEmpty())
        res.removeLast();

    return res;
}

QStringList GTApiTranslation::original() const
{
    QStringList res;
    foreach( const GTReplyObject &sentence, root[0] )
        res << sentence[1].toString();

    if (!res.isEmpty())
        res.removeLast();

    return res;
}

QString GTApiTranslation::translit() const
{
    return root[0][ root[0].size()-1 ][2].toString();
}

QString GTApiTranslation::srcTranslit() const
{
    return root[0][ root[0].size()-1 ][3].toString();
}

QString GTApiTranslation::srcLang() const
{
    return root[2].toString();
}

QList<GTPosDict> GTApiTranslation::getPosDictionary() const
{
    QList<GTPosDict> res;

    foreach ( const GTReplyObject gtDict, root[1] ) {

        GTPosDict dictPos;
        dictPos.posNameHl    = gtDict[0].toString();
        dictPos.posDictEnum  = (GTPosDictEnum)(static_cast<int>(gtDict[4].toNum()));
        dictPos.wordSourceBaseForm = gtDict[3].toString();

        foreach (const GTReplyObject gtDictEntry, gtDict[2]) {

            GTPosDictEntry dictPosEntry;
            dictPosEntry.wordTarget         = gtDictEntry[0].toString();
            dictPosEntry.wordRetranslations = gtDictEntry[1].toStringList();
            dictPosEntry.synsetIds  = gtDictEntry[2].toStringList();
            dictPosEntry.score      = gtDictEntry[3].toNum();
            dictPosEntry.previousWordTarge  = gtDictEntry[4].toString();

            dictPos.entries.append(dictPosEntry);
        }

        res.append(dictPos);
    }
    return res;
}

QList<GTDefDict> GTApiTranslation::getDefDictionary() const
{
    QList<GTDefDict> res;

    foreach ( const GTReplyObject gtDict, root[12] ) {

        GTDefDict dictDef;
        dictDef.posName         = gtDict[0].toString();
        dictDef.wordBaseForm    = gtDict[2].toString();

        foreach (const GTReplyObject gtDictEntry, gtDict[2]) {

            GTDefDictEntry dictDefEntry;
            dictDefEntry.definition = gtDictEntry[0].toString();
            dictDefEntry.word_id    = gtDictEntry[1].toString();
            dictDefEntry.definitionExampleUsage = gtDictEntry[2].toString();

            dictDef.entries.append(dictDefEntry);
        }

        res.append(dictDef);
    }
    return res;
}

const GTReplyObject & GTApiTranslation::replyObjectRef() const
{
    return root;
}