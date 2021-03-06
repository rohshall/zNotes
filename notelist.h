#ifndef NOTELIST_H
#define NOTELIST_H

#include "note.h"
#include "notetype.h"
#include "ztabwidget.h"

#include <QVector>
#include <QList>
#include <QObject>
#include <QSet>
#include <QMap>
#include <QDir>

class QFileSystemWatcher;

class NoteList : public QObject
{
	Q_OBJECT
public:
	NoteList(QWidget* parent = 0);
	~NoteList();
	//
	inline bool empty() const {return vec.isEmpty(); }
	inline int count() const { return vec.size(); }
	inline int last() const { return vec.size()-1; }
	inline void setCurrent(int n) { tabs->setCurrentIndex(n); }
    inline Note* current() const { return (current_index != -1) ? vec[current_index] : 0; }
	inline Note* get(int i) const { return (vec.size()>i)?vec[i]:0; }
	inline int currentIndex() const { return current_index; }
	inline bool historyHasBack() const { return history_index>0; }
	inline bool historyHasForward() const { return (history_index+1)<history.size(); }
	//
	void create(Note::Type type, const QString& name = QString());
	//
	void search(const QString& text);
	//
	inline ZTabWidget* getWidget() const { return tabs; }
	//
	void retranslate(const QLocale& locale);
	//
	inline const QMap<Note::Type,NoteType>& noteTypes() { return note_types; }
	void registerType(Note::Type id, const QString& title,
					  const QString& description, const QString& big_icon_path,
					  const QString& small_icon_path, const QString extensions,
					  bool visible = true);
public slots:
    void saveAll();
    //
    void removeCurrentNote();
    void renameCurrentNote();
    //
    void historyBack();
    void historyForward();

private:
	void initNoteTypes();
	Note::Type getType(const QFileInfo& fileinfo) const;
	Note* add(const QFileInfo& fileinfo, bool set_current = true);
	void remove(int i);
	void rename(int index, const QString& title);
    void move(const QString &newPath, const QString &oldPath);

    // File with format INI for saving cursor position of a note.
    const QString FILE_WITH_CURSOR_POSITIONS;

    QWidget *parentWidget;

    QMap<Note::Type,NoteType> note_types;
    QMap<QString, Note::Type> NOTE_TYPE_MAP;

    // Next group of data is syncronized
    QSet<QString> notes_filenames;
    QList<Note*> vec;
    //
    QList<QString> history;
    int history_index;
    bool history_forward_pressed;
    bool history_back_pressed;
    //
    int current_index;
    ZTabWidget* tabs;
    //
    QFileSystemWatcher* watcher;
    QDir dir;

private slots:
	void currentTabChanged(int index);
	void showExtensionsChanged(bool show_extensions);
	void tabPositionChanged();
	void notesPathChanged();
	void scanForNewFiles();
    void changeNoteName(int);

signals:
	void currentNoteChanged(int old_index, int new_index);
};

#endif // NOTELIST_H
