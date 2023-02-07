#include <gtk/gtk.h>
#include <glib/gstdio.h>
#include "parson.h"
#include <stdio.h>

GtkApplication *app;
GObject *window;
GObject *selectTerminalWindow;
GtkWidget *fixed1;

// Wordlist Generator Edits
GtkWidget *editWGMarkovChainFile;
GtkWidget *editWGWordlistMapFile;
GtkWidget *editWGOutputFile;
GtkWidget *editWGNumber;
GtkWidget *editWGThreads;
GtkWidget *editWGMinWordLength;
GtkWidget *editWGMaxWordLength;

// Other Wordlist Generator Widgets
GtkWidget *checkboxWGMinWordLength;
GtkWidget *checkboxWGMaxWordLength;
GtkWidget *radioButtonWGWeighted;
GtkWidget *radioButtonWGHalfWeighted;
GtkWidget *radioButtonWGUnweighted;

// Markov Chain Thing Edits
GtkWidget *editMCWordlist;
GtkWidget *editMCOutput;

// Wordlist Mapper Edits
GtkWidget *editWMWordlist;
GtkWidget *editWMOutput;

// Settings Edits
GtkWidget *editSTerminalCommandLine;
GtkWidget *editSWordlistGenerator;
GtkWidget *editSMarkovChainThing;
GtkWidget *editSWordlistMapper;
GtkWidget *comboSelectTerminal;

static void on_window_close_request(GtkWidget *w);
static void on_selectTerminalWindow_close_request(GtkWidget *w);

void buttonWGMarkovChainFileOpen_clicked_cb(GtkButton *b);
void buttonWGWordlistMapFileOpen_clicked_cb(GtkButton *b);
void buttonWGOutputFileOpen_clicked_cb(GtkButton *b);
void buttonMCWordlistBrowse_clicked_cb(GtkButton *b);
void buttonMCOutputBrowse_clicked_cb(GtkButton *b);
void buttonWMWordlistBrowse_clicked_cb(GtkButton *b);
void buttonWMOutputBrowse_clicked_cb(GtkButton *b);
void buttonSWordlistGeneratorBrowse_clicked_cb(GtkButton *b);
void buttonSMarkovChainThingBrowse_clicked_cb(GtkButton *b);
void buttonSWordlistMapperBrowse_clicked_cb(GtkButton *b);

static void on_WGMarkovChainOpen_response(GtkDialog *dialog, int response);
static void on_WGWordlistMapOpen_response(GtkDialog *dialog, int response);
static void on_WGOutputSave_response(GtkDialog *dialog, int response);
static void on_MCWordlistOpen_response(GtkDialog *dialog, int response);
static void on_MCOutputSave_response(GtkDialog *dialog, int response);
static void on_WMWordlistOpen_response(GtkDialog *dialog, int response);
static void on_WMOutputSave_response(GtkDialog *dialog, int response);
static void on_SWordlistGeneratorOpen_response(GtkDialog *dialog, int response);
static void on_SMarkovChainThingOpen_response(GtkDialog *dialog, int response);
static void on_SWordlistMapperOpen_response(GtkDialog *dialog, int response);

void checkboxWFMinWordLength_toggled_cb(GtkCheckButton *cb);
void checkboxWGMaxWordLength_toggled_cb(GtkCheckButton *cb);
void buttonWGGenerate_clicked_cb(GtkButton *b);
void buttonSTerminalCommandLineEdit_clicked_cb(GtkButton *b);
void buttonSelectTerminalOK_clicked_cb(GtkButton *b);
void buttonSelectTerminalCancel_clicked_cb(GtkButton *b);
void buttonMCGenerate_clicked_cb(GtkButton *b);
void buttonWMGenerate_clicked_cb(GtkButton *b);
void buttonSResetToDefault_clicked_cb(GtkButton *b);

// JSON Funcions
void writeJSONToFile(void);
void loadJSONFromFile(void);

static void activate(GtkApplication *app, gpointer user_data)
{
    /* Construct a GtkBuilder instance and load our UI description */
    GtkBuilder *builder = gtk_builder_new_from_file("./Resources/WordlistZombieGUI.gtk4.glade");

    /* Connect signal handlers to the constructed widgets. */
    window = gtk_builder_get_object(builder, "mainWindow");
    gtk_window_set_application(GTK_WINDOW(window), app);
    selectTerminalWindow = gtk_builder_get_object(builder, "selectTerminalWindow");

    g_signal_connect(window, "close-request", G_CALLBACK(on_window_close_request), NULL);
    g_signal_connect(selectTerminalWindow, "close-request", G_CALLBACK(on_selectTerminalWindow_close_request), NULL);

    fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
    editWGMarkovChainFile = GTK_WIDGET(gtk_builder_get_object(builder, "editWGMarkovChainFile"));
    editWGWordlistMapFile = GTK_WIDGET(gtk_builder_get_object(builder, "editWGWordlistMapFile"));
    editWGOutputFile = GTK_WIDGET(gtk_builder_get_object(builder, "editWGOutputFile"));
    editWGNumber = GTK_WIDGET(gtk_builder_get_object(builder, "editWGNumber"));
    editWGThreads = GTK_WIDGET(gtk_builder_get_object(builder, "editWGThreads"));
    editWGMinWordLength = GTK_WIDGET(gtk_builder_get_object(builder, "editWGMinWordLength"));
    editWGMaxWordLength = GTK_WIDGET(gtk_builder_get_object(builder, "editWGMaxWordLength"));
    checkboxWGMinWordLength = GTK_WIDGET(gtk_builder_get_object(builder, "checkboxWGMinWordLength"));
    checkboxWGMaxWordLength = GTK_WIDGET(gtk_builder_get_object(builder, "checkboxWGMaxWordLength"));
    radioButtonWGWeighted = GTK_WIDGET(gtk_builder_get_object(builder, "radioButtonWGWeighted"));
    radioButtonWGHalfWeighted = GTK_WIDGET(gtk_builder_get_object(builder, "radioButtonWGHalfWeighted"));
    radioButtonWGUnweighted = GTK_WIDGET(gtk_builder_get_object(builder, "radioButtonWGUnweighted"));
    editMCWordlist = GTK_WIDGET(gtk_builder_get_object(builder, "editMCWordlist"));
    editMCOutput = GTK_WIDGET(gtk_builder_get_object(builder, "editMCOutput"));
    editWMWordlist = GTK_WIDGET(gtk_builder_get_object(builder, "editWMWordlist"));
    editWMOutput = GTK_WIDGET(gtk_builder_get_object(builder, "editWMOutput"));
    editSTerminalCommandLine = GTK_WIDGET(gtk_builder_get_object(builder, "editSTerminalCommandLine"));
    editSWordlistGenerator = GTK_WIDGET(gtk_builder_get_object(builder, "editSWordlistGenerator"));
    editSMarkovChainThing = GTK_WIDGET(gtk_builder_get_object(builder, "editSMarkovChainThing"));
    editSWordlistMapper = GTK_WIDGET(gtk_builder_get_object(builder, "editSWordlistMapper"));
    comboSelectTerminal = GTK_WIDGET(gtk_builder_get_object(builder, "comboSelectTerminal"));

    // Load Cool image
    GtkWidget *picture1 = gtk_picture_new_for_filename("./Resources/WordlistZombie.png");
    gtk_fixed_put(GTK_FIXED(fixed1), picture1, 104, 10);
    gtk_widget_set_size_request(picture1, 530, 107);

    // Set Default Threads
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(editWGThreads));
    gtk_entry_buffer_set_text(buffer, "50", -1);

    // Set Default Settings
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editSTerminalCommandLine));
    gtk_entry_buffer_set_text(buffer, "gnome-terminal -- bash -c '%s; exec bash'", -1);
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editSWordlistGenerator));
    gtk_entry_buffer_set_text(buffer, "./WordlistGenerator", -1);
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editSMarkovChainThing));
    gtk_entry_buffer_set_text(buffer, "./MarkovChainThing", -1);
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editSWordlistMapper));
    gtk_entry_buffer_set_text(buffer, "./WordlistMapper", -1);

    loadJSONFromFile();

    gtk_widget_show(GTK_WIDGET(window));
    g_object_unref(builder);
}

int main(int argc, char *argv[])
{

#ifdef GTK_SRCDIR
    g_chdir(GTK_SRCDIR);
#endif

    app = gtk_application_new(NULL, G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}

static void on_window_close_request(GtkWidget *w)
{
    writeJSONToFile();
    g_application_quit(G_APPLICATION(app));
}

static void on_selectTerminalWindow_close_request(GtkWidget *w)
{
    gtk_widget_hide(w);
    return;
}

///////////////////////////////////////////////////////////////////////////
//
//
//
//   Browse Button Callbacks
//
//
//
///////////////////////////////////////////////////////////////////////////

void buttonWGMarkovChainFileOpen_clicked_cb(GtkButton *b)
{
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
    gtk_window_present(GTK_WINDOW(dialog));
    g_signal_connect(dialog, "response", G_CALLBACK(on_WGMarkovChainOpen_response), NULL);
    return;
}

void buttonWGWordlistMapFileOpen_clicked_cb(GtkButton *b)
{
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
    gtk_window_present(GTK_WINDOW(dialog));
    g_signal_connect(dialog, "response", G_CALLBACK(on_WGWordlistMapOpen_response), NULL);
    return;
}

void buttonWGOutputFileOpen_clicked_cb(GtkButton *b)
{
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Save File", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_SAVE, "_Cancel", GTK_RESPONSE_CANCEL, "_Save", GTK_RESPONSE_ACCEPT, NULL);
    GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
    gtk_file_chooser_set_current_name(chooser, "Output.txt");
    gtk_window_present(GTK_WINDOW(dialog));
    g_signal_connect(dialog, "response", G_CALLBACK(on_WGOutputSave_response), NULL);
    return;
}

void buttonMCWordlistBrowse_clicked_cb(GtkButton *b)
{
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
    gtk_window_present(GTK_WINDOW(dialog));
    g_signal_connect(dialog, "response", G_CALLBACK(on_MCWordlistOpen_response), NULL);
    return;
}

void buttonMCOutputBrowse_clicked_cb(GtkButton *b)
{
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Save File", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_SAVE, "_Cancel", GTK_RESPONSE_CANCEL, "_Save", GTK_RESPONSE_ACCEPT, NULL);
    GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
    gtk_file_chooser_set_current_name(chooser, "Output.txt");
    gtk_window_present(GTK_WINDOW(dialog));
    g_signal_connect(dialog, "response", G_CALLBACK(on_MCOutputSave_response), NULL);
    return;
}

void buttonWMWordlistBrowse_clicked_cb(GtkButton *b)
{
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
    gtk_window_present(GTK_WINDOW(dialog));
    g_signal_connect(dialog, "response", G_CALLBACK(on_WMWordlistOpen_response), NULL);
    return;
}

void buttonWMOutputBrowse_clicked_cb(GtkButton *b)
{
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Save File", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_SAVE, "_Cancel", GTK_RESPONSE_CANCEL, "_Save", GTK_RESPONSE_ACCEPT, NULL);
    GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
    gtk_file_chooser_set_current_name(chooser, "Output.txt");
    gtk_window_present(GTK_WINDOW(dialog));
    g_signal_connect(dialog, "response", G_CALLBACK(on_WMOutputSave_response), NULL);
    return;
}

void buttonSWordlistGeneratorBrowse_clicked_cb(GtkButton *b)
{
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
    gtk_window_present(GTK_WINDOW(dialog));
    g_signal_connect(dialog, "response", G_CALLBACK(on_SWordlistGeneratorOpen_response), NULL);
    return;
}

void buttonSMarkovChainThingBrowse_clicked_cb(GtkButton *b)
{
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
    gtk_window_present(GTK_WINDOW(dialog));
    g_signal_connect(dialog, "response", G_CALLBACK(on_SMarkovChainThingOpen_response), NULL);
    return;
}

void buttonSWordlistMapperBrowse_clicked_cb(GtkButton *b)
{
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
    gtk_window_present(GTK_WINDOW(dialog));
    g_signal_connect(dialog, "response", G_CALLBACK(on_SWordlistMapperOpen_response), NULL);
    return;
}

//////////////////////////////////////////////////////////////////////////
//
//
//
//  Open and Save File Dialog Callbacks
//
//
//
//////////////////////////////////////////////////////////////////////////

static void on_WGMarkovChainOpen_response(GtkDialog *dialog, int response)
{
    GtkEntryBuffer *buffer;

    if (response == GTK_RESPONSE_ACCEPT)
    {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        g_autoptr(GFile) file = gtk_file_chooser_get_file(chooser);
        buffer = gtk_entry_get_buffer(GTK_ENTRY(editWGMarkovChainFile));
        gtk_entry_buffer_set_text(buffer, g_file_get_path(file), -1);
    }

    gtk_window_destroy(GTK_WINDOW(dialog));
}

static void on_WGWordlistMapOpen_response(GtkDialog *dialog, int response)
{
    GtkEntryBuffer *buffer;

    if (response == GTK_RESPONSE_ACCEPT)
    {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        g_autoptr(GFile) file = gtk_file_chooser_get_file(chooser);
        buffer = gtk_entry_get_buffer(GTK_ENTRY(editWGWordlistMapFile));
        gtk_entry_buffer_set_text(buffer, g_file_get_path(file), -1);
    }

    gtk_window_destroy(GTK_WINDOW(dialog));
}

static void on_WGOutputSave_response(GtkDialog *dialog, int response)
{
    GtkEntryBuffer *buffer;

    if (response == GTK_RESPONSE_ACCEPT)
    {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        g_autoptr(GFile) file = gtk_file_chooser_get_file(chooser);
        buffer = gtk_entry_get_buffer(GTK_ENTRY(editWGOutputFile));
        gtk_entry_buffer_set_text(buffer, g_file_get_path(file), -1);
    }
    gtk_window_destroy(GTK_WINDOW(dialog));
}

static void on_MCWordlistOpen_response(GtkDialog *dialog, int response)
{
    GtkEntryBuffer *buffer;

    if (response == GTK_RESPONSE_ACCEPT)
    {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        g_autoptr(GFile) file = gtk_file_chooser_get_file(chooser);
        buffer = gtk_entry_get_buffer(GTK_ENTRY(editMCWordlist));
        gtk_entry_buffer_set_text(buffer, g_file_get_path(file), -1);
    }

    gtk_window_destroy(GTK_WINDOW(dialog));
}

static void on_MCOutputSave_response(GtkDialog *dialog, int response)
{
    GtkEntryBuffer *buffer;

    if (response == GTK_RESPONSE_ACCEPT)
    {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        g_autoptr(GFile) file = gtk_file_chooser_get_file(chooser);
        buffer = gtk_entry_get_buffer(GTK_ENTRY(editMCOutput));
        gtk_entry_buffer_set_text(buffer, g_file_get_path(file), -1);
    }
    gtk_window_destroy(GTK_WINDOW(dialog));
}

static void on_WMWordlistOpen_response(GtkDialog *dialog, int response)
{
    GtkEntryBuffer *buffer;

    if (response == GTK_RESPONSE_ACCEPT)
    {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        g_autoptr(GFile) file = gtk_file_chooser_get_file(chooser);
        buffer = gtk_entry_get_buffer(GTK_ENTRY(editWMWordlist));
        gtk_entry_buffer_set_text(buffer, g_file_get_path(file), -1);
    }

    gtk_window_destroy(GTK_WINDOW(dialog));
}

static void on_WMOutputSave_response(GtkDialog *dialog, int response)
{
    GtkEntryBuffer *buffer;

    if (response == GTK_RESPONSE_ACCEPT)
    {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        g_autoptr(GFile) file = gtk_file_chooser_get_file(chooser);
        buffer = gtk_entry_get_buffer(GTK_ENTRY(editWMOutput));
        gtk_entry_buffer_set_text(buffer, g_file_get_path(file), -1);
    }
    gtk_window_destroy(GTK_WINDOW(dialog));
}

static void on_SWordlistGeneratorOpen_response(GtkDialog *dialog, int response)
{
    GtkEntryBuffer *buffer;

    if (response == GTK_RESPONSE_ACCEPT)
    {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        g_autoptr(GFile) file = gtk_file_chooser_get_file(chooser);
        buffer = gtk_entry_get_buffer(GTK_ENTRY(editSWordlistGenerator));
        gtk_entry_buffer_set_text(buffer, g_file_get_path(file), -1);
    }

    gtk_window_destroy(GTK_WINDOW(dialog));
}

static void on_SMarkovChainThingOpen_response(GtkDialog *dialog, int response)
{
    GtkEntryBuffer *buffer;

    if (response == GTK_RESPONSE_ACCEPT)
    {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        g_autoptr(GFile) file = gtk_file_chooser_get_file(chooser);
        buffer = gtk_entry_get_buffer(GTK_ENTRY(editSMarkovChainThing));
        gtk_entry_buffer_set_text(buffer, g_file_get_path(file), -1);
    }

    gtk_window_destroy(GTK_WINDOW(dialog));
}

static void on_SWordlistMapperOpen_response(GtkDialog *dialog, int response)
{
    GtkEntryBuffer *buffer;

    if (response == GTK_RESPONSE_ACCEPT)
    {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        g_autoptr(GFile) file = gtk_file_chooser_get_file(chooser);
        buffer = gtk_entry_get_buffer(GTK_ENTRY(editSWordlistMapper));
        gtk_entry_buffer_set_text(buffer, g_file_get_path(file), -1);
    }

    gtk_window_destroy(GTK_WINDOW(dialog));
}

///////////////////////////////////////////////////////////////////////////
//
//
//
//   Other Widget Callbacks
//
//
//
////////////////////////////////////////////////////////////////////////////

void checkboxWFMinWordLength_toggled_cb(GtkCheckButton *cb)
{
    if (gtk_check_button_get_active(cb))
    {
        gtk_editable_set_editable(GTK_EDITABLE(editWGMinWordLength), true);
        gtk_widget_set_opacity(editWGMinWordLength, 1.0);
    }
    else
    {
        gtk_editable_set_editable(GTK_EDITABLE(editWGMinWordLength), false);
        gtk_widget_set_opacity(editWGMinWordLength, 0.5);
    }
    return;
}

void checkboxWGMaxWordLength_toggled_cb(GtkCheckButton *cb)
{
    if (gtk_check_button_get_active(cb))
    {
        gtk_editable_set_editable(GTK_EDITABLE(editWGMaxWordLength), true);
        gtk_widget_set_opacity(editWGMaxWordLength, 1.0);
    }
    else
    {
        gtk_editable_set_editable(GTK_EDITABLE(editWGMaxWordLength), false);
        gtk_widget_set_opacity(editWGMaxWordLength, 0.5);
    }
    return;
}

void buttonWGGenerate_clicked_cb(GtkButton *b)
{
    char formatbuff[4096];
    char outbuff[4096];
    char *format = "\"%s\" --number %s --markov \"%s\" --wordmap \"%s\" --output \"%s\"";
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(editSTerminalCommandLine));
    char *terminalCommandLine = (char *)gtk_entry_buffer_get_text(buffer);

    buffer = gtk_entry_get_buffer(GTK_ENTRY(editSWordlistGenerator));
    char *pathWordlistGenerator = (char *)gtk_entry_buffer_get_text(buffer);

    buffer = gtk_entry_get_buffer(GTK_ENTRY(editWGNumber));
    char *wGNumber = (char *)gtk_entry_buffer_get_text(buffer);

    buffer = gtk_entry_get_buffer(GTK_ENTRY(editWGMarkovChainFile));
    char *wGMarkovChainFile = (char *)gtk_entry_buffer_get_text(buffer);

    buffer = gtk_entry_get_buffer(GTK_ENTRY(editWGWordlistMapFile));
    char *wGWordlistMapFile = (char *)gtk_entry_buffer_get_text(buffer);

    buffer = gtk_entry_get_buffer(GTK_ENTRY(editWGOutputFile));
    char *wGOutputFile = (char *)gtk_entry_buffer_get_text(buffer);

    sprintf(formatbuff, format, pathWordlistGenerator, wGNumber, wGMarkovChainFile, wGWordlistMapFile, wGOutputFile);

    // Threads
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editWGThreads));
    char *wGThreads = (char *)gtk_entry_buffer_get_text(buffer);

    if (strcmp(wGThreads, "50") != 0)
    {
        strcat(formatbuff, " --threads ");
        strcat(formatbuff, wGThreads);
    }

    // Min Word Length
    if (gtk_check_button_get_active(GTK_CHECK_BUTTON(checkboxWGMinWordLength)))
    {
        // Min Word Length is checked!
        buffer = gtk_entry_get_buffer(GTK_ENTRY(editWGMinWordLength));
        char *wGMinWordLength = (char *)gtk_entry_buffer_get_text(buffer);
        strcat(formatbuff, " --minwordlength ");
        strcat(formatbuff, wGMinWordLength);
    }

    // Max Word Length
    if (gtk_check_button_get_active(GTK_CHECK_BUTTON(checkboxWGMaxWordLength)))
    {
        // Max Word Length is checked!
        buffer = gtk_entry_get_buffer(GTK_ENTRY(editWGMaxWordLength));
        char *wGMaxWordLength = (char *)gtk_entry_buffer_get_text(buffer);
        strcat(formatbuff, " --maxwordlength ");
        strcat(formatbuff, wGMaxWordLength);
    }

    if (gtk_check_button_get_active(GTK_CHECK_BUTTON(radioButtonWGHalfWeighted)))
    {
        strcat(formatbuff, " --halfweighted");
    }

    if (gtk_check_button_get_active(GTK_CHECK_BUTTON(radioButtonWGUnweighted)))
    {
        strcat(formatbuff, " --unweighted");
    }

    sprintf(outbuff, terminalCommandLine, formatbuff);

    system(outbuff);

    return;
}

void buttonSTerminalCommandLineEdit_clicked_cb(GtkButton *b)
{
    gtk_widget_show(GTK_WIDGET(selectTerminalWindow));
    return;
}

void buttonSelectTerminalOK_clicked_cb(GtkButton *b)
{
    gchar *comboText = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboSelectTerminal));
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(editSTerminalCommandLine));
    gtk_entry_buffer_set_text(buffer, comboText, -1);
    gtk_widget_hide(GTK_WIDGET(selectTerminalWindow));
    return;
}

void buttonSelectTerminalCancel_clicked_cb(GtkButton *b)
{
    gtk_widget_hide(GTK_WIDGET(selectTerminalWindow));
    return;
}

void buttonMCGenerate_clicked_cb(GtkButton *b)
{
    char formatbuff[4096];
    char outbuff[4096];
    char *format = "\"%s\" --wordlist \"%s\" --output \"%s\"";
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(editSTerminalCommandLine));
    char *terminalCommandLine = (char *)gtk_entry_buffer_get_text(buffer);

    buffer = gtk_entry_get_buffer(GTK_ENTRY(editSMarkovChainThing));
    char *pathMarkovChain = (char *)gtk_entry_buffer_get_text(buffer);

    buffer = gtk_entry_get_buffer(GTK_ENTRY(editMCWordlist));
    char *mCWordlist = (char *)gtk_entry_buffer_get_text(buffer);

    buffer = gtk_entry_get_buffer(GTK_ENTRY(editMCOutput));
    char *mCOutput = (char *)gtk_entry_buffer_get_text(buffer);

    sprintf(formatbuff, format, pathMarkovChain, mCWordlist, mCOutput);
    sprintf(outbuff, terminalCommandLine, formatbuff);

    system(outbuff);
    return;
}

void buttonWMGenerate_clicked_cb(GtkButton *b)
{
    char formatbuff[4096];
    char outbuff[4096];
    char *format = "\"%s\" --wordlist \"%s\" --output \"%s\"";
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(editSTerminalCommandLine));
    char *terminalCommandLine = (char *)gtk_entry_buffer_get_text(buffer);

    buffer = gtk_entry_get_buffer(GTK_ENTRY(editSWordlistMapper));
    char *pathWordlistMapper = (char *)gtk_entry_buffer_get_text(buffer);

    buffer = gtk_entry_get_buffer(GTK_ENTRY(editWMWordlist));
    char *wMWordlist = (char *)gtk_entry_buffer_get_text(buffer);

    buffer = gtk_entry_get_buffer(GTK_ENTRY(editWMOutput));
    char *wMOutput = (char *)gtk_entry_buffer_get_text(buffer);

    sprintf(formatbuff, format, pathWordlistMapper, wMWordlist, wMOutput);
    sprintf(outbuff, terminalCommandLine, formatbuff);

    system(outbuff);
    return;
}

void buttonSResetToDefault_clicked_cb(GtkButton *b)
{
    // Set Default Settings
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(editSTerminalCommandLine));
    gtk_entry_buffer_set_text(buffer, "gnome-terminal -- bash -c '%s; exec bash'", -1);
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editSWordlistGenerator));
    gtk_entry_buffer_set_text(buffer, "./WordlistGenerator", -1);
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editSMarkovChainThing));
    gtk_entry_buffer_set_text(buffer, "./MarkovChainThing", -1);
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editSWordlistMapper));
    gtk_entry_buffer_set_text(buffer, "./WordlistMapper", -1);
    return;
}

////////////////////////////////////////////////////////////////////////////
//
//
//
//   JSON Functions
//
//
//
////////////////////////////////////////////////////////////////////////////

void writeJSONToFile(void)
{

    // Wordlist Generator Edits
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(editWGMarkovChainFile));
    char *wGMarkovChainFile = (char *)gtk_entry_buffer_get_text(buffer);
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editWGWordlistMapFile));
    char *wGWordlistMapFile = (char *)gtk_entry_buffer_get_text(buffer);
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editWGOutputFile));
    char *wGOutputFile = (char *)gtk_entry_buffer_get_text(buffer);
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editWGNumber));
    char *wGNumber = (char *)gtk_entry_buffer_get_text(buffer);
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editWGThreads));
    char *wGThreads = (char *)gtk_entry_buffer_get_text(buffer);
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editWGMinWordLength));
    char *wGMinWordLength = (char *)gtk_entry_buffer_get_text(buffer);
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editWGMaxWordLength));
    char *wGMaxWordLength = (char *)gtk_entry_buffer_get_text(buffer);

    // Other Wordlist Generator Widgets
    bool cbWGMinWordLength = gtk_check_button_get_active(GTK_CHECK_BUTTON(checkboxWGMinWordLength));
    bool cbWGMaxWordLength = gtk_check_button_get_active(GTK_CHECK_BUTTON(checkboxWGMaxWordLength));
    bool rbWGWeighted = gtk_check_button_get_active(GTK_CHECK_BUTTON(radioButtonWGWeighted));
    bool rbWGHalfWeighted = gtk_check_button_get_active(GTK_CHECK_BUTTON(radioButtonWGHalfWeighted));
    bool rbWGUnweighted = gtk_check_button_get_active(GTK_CHECK_BUTTON(radioButtonWGUnweighted));

    // Markov Chain Thing Edits
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editMCWordlist));
    char *mCWordlist = (char *)gtk_entry_buffer_get_text(buffer);
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editMCOutput));
    char *mCOutput = (char *)gtk_entry_buffer_get_text(buffer);

    // Wordlist Mapper Edits
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editWMWordlist));
    char *wMWordlist = (char *)gtk_entry_buffer_get_text(buffer);
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editWMOutput));
    char *wMOutput = (char *)gtk_entry_buffer_get_text(buffer);

    // Settings Edits
    // editSTerminalCommandLine;
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editSTerminalCommandLine));
    char *sTerminalCommandLine = (char *)gtk_entry_buffer_get_text(buffer);
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editSWordlistGenerator));
    char *sWordlistGenerator = (char *)gtk_entry_buffer_get_text(buffer);
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editSMarkovChainThing));
    char *sMarkovChainThing = (char *)gtk_entry_buffer_get_text(buffer);
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editSWordlistMapper));
    char *sWordlistMapper = (char *)gtk_entry_buffer_get_text(buffer);

    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);
    char *serialized_string = NULL;
    json_object_set_string(root_object, "editWGMarkovChainFile", wGMarkovChainFile);
    json_object_set_string(root_object, "editWGWordlistMapFile", wGWordlistMapFile);
    json_object_set_string(root_object, "editWGOutputFile", wGOutputFile);
    json_object_set_string(root_object, "editWGNumber", wGNumber);
    json_object_set_string(root_object, "editWGThreads", wGThreads);
    json_object_set_string(root_object, "editWGMinWordLength", wGMinWordLength);
    json_object_set_string(root_object, "editWGMaxWordLength", wGMaxWordLength);
    json_object_set_boolean(root_object, "checkboxWGMinWordLength", cbWGMinWordLength);
    json_object_set_boolean(root_object, "checkboxWGMaxWordLength", cbWGMaxWordLength);
    json_object_set_boolean(root_object, "radioButtonWGWeighted", rbWGWeighted);
    json_object_set_boolean(root_object, "radioButtonWGHalfWeighted", rbWGHalfWeighted);
    json_object_set_boolean(root_object, "radioButtonWGUnweighted", rbWGUnweighted);
    json_object_set_string(root_object, "editMCWordlist", mCWordlist);
    json_object_set_string(root_object, "editMCOutput", mCOutput);
    json_object_set_string(root_object, "editWMWordlist", wMWordlist);
    json_object_set_string(root_object, "editWMOutput", wMOutput);
    json_object_set_string(root_object, "editSTerminalCommandLine", sTerminalCommandLine);
    json_object_set_string(root_object, "editSWordlistGenerator", sWordlistGenerator);
    json_object_set_string(root_object, "editSMarkovChainThing", sMarkovChainThing);
    json_object_set_string(root_object, "editSWordlistMapper", sWordlistMapper);

    serialized_string = json_serialize_to_string_pretty(root_value);

    FILE *fp = fopen("./Resources/settings.json", "w");
    if (fp == NULL)
        return;

    fwrite(serialized_string, 1, strlen(serialized_string), fp);
    fclose(fp);

    json_free_serialized_string(serialized_string);
    json_value_free(root_value);
    return;
}

void loadJSONFromFile(void)
{
    JSON_Value *root_value = json_parse_file("./Resources/settings.json");
    if (root_value == NULL) return;

    char *wGMarkovChainFile = (char *)json_object_get_string(json_object(root_value), "editWGMarkovChainFile");
    char *wGWordlistMapFile = (char *)json_object_get_string(json_object(root_value), "editWGWordlistMapFile");
    char *wGOutputFile = (char *)json_object_get_string(json_object(root_value), "editWGOutputFile");
    char *wGNumber = (char *)json_object_get_string(json_object(root_value), "editWGNumber");
    char *wGThreads = (char *)json_object_get_string(json_object(root_value), "editWGThreads");
    char *wGMinWordLength = (char *)json_object_get_string(json_object(root_value), "editWGMinWordLength");
    char *wGMaxWordLength = (char *)json_object_get_string(json_object(root_value), "editWGMaxWordLength");
    bool cbWGMinWordLength = json_object_get_boolean(json_object(root_value), "checkboxWGMinWordLength");
    bool cbWGMaxWordLength = json_object_get_boolean(json_object(root_value), "checkboxWGMaxWordLength");
    bool rbWGWeighted = json_object_get_boolean(json_object(root_value), "radioButtonWGWeighted");
    bool rbWGHalfWeighted = json_object_get_boolean(json_object(root_value), "radioButtonWGHalfWeighted");
    bool rbWGUnweighted = json_object_get_boolean(json_object(root_value), "radioButtonWGUnweighted");
    char *mCWordlist = (char *)json_object_get_string(json_object(root_value), "editMCWordlist");
    char *mCOutput = (char *)json_object_get_string(json_object(root_value), "editMCOutput");
    char *wMWordlist = (char *)json_object_get_string(json_object(root_value), "editWMWordlist");
    char *wMOutput = (char *)json_object_get_string(json_object(root_value), "editWMOutput");
    char *sTerminalCommandLine = (char *)json_object_get_string(json_object(root_value), "editSTerminalCommandLine");
    char *sWordlistGenerator = (char *)json_object_get_string(json_object(root_value), "editSWordlistGenerator");
    char *sMarkovChainThing = (char *)json_object_get_string(json_object(root_value), "editSMarkovChainThing");
    char *sWordlistMapper = (char *)json_object_get_string(json_object(root_value), "editSWordlistMapper");

    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(editWGMarkovChainFile));
    gtk_entry_buffer_set_text(buffer, wGMarkovChainFile, -1);
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editWGWordlistMapFile));
    gtk_entry_buffer_set_text(buffer, wGWordlistMapFile, -1);
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editWGOutputFile));
    gtk_entry_buffer_set_text(buffer, wGOutputFile, -1);
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editWGNumber));
    gtk_entry_buffer_set_text(buffer, wGNumber, -1);
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editWGThreads));
    gtk_entry_buffer_set_text(buffer, wGThreads, -1);
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editWGMinWordLength));
    gtk_entry_buffer_set_text(buffer, wGMinWordLength, -1);
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editWGMaxWordLength));
    gtk_entry_buffer_set_text(buffer, wGMaxWordLength, -1);
    gtk_check_button_set_active(GTK_CHECK_BUTTON(checkboxWGMinWordLength), cbWGMinWordLength);
    gtk_check_button_set_active(GTK_CHECK_BUTTON(checkboxWGMaxWordLength), cbWGMaxWordLength);
    gtk_check_button_set_active(GTK_CHECK_BUTTON(radioButtonWGWeighted), rbWGWeighted);
    gtk_check_button_set_active(GTK_CHECK_BUTTON(radioButtonWGHalfWeighted), rbWGHalfWeighted);
    gtk_check_button_set_active(GTK_CHECK_BUTTON(radioButtonWGUnweighted), rbWGUnweighted);
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editMCWordlist));
    gtk_entry_buffer_set_text(buffer, mCWordlist, -1);
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editMCOutput));
    gtk_entry_buffer_set_text(buffer, mCOutput, -1);
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editWMWordlist));
    gtk_entry_buffer_set_text(buffer, wMWordlist, -1);
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editWMOutput));
    gtk_entry_buffer_set_text(buffer, wMOutput, -1);
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editSTerminalCommandLine));
    gtk_entry_buffer_set_text(buffer, sTerminalCommandLine, -1);
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editSWordlistGenerator));
    gtk_entry_buffer_set_text(buffer, sWordlistGenerator, -1);
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editSMarkovChainThing));
    gtk_entry_buffer_set_text(buffer, sMarkovChainThing, -1);
    buffer = gtk_entry_get_buffer(GTK_ENTRY(editSWordlistMapper));
    gtk_entry_buffer_set_text(buffer, sWordlistMapper, -1);
    
    json_value_free(root_value);
    return;
}