#include "MainWindow.h"

#define MAIN_WINDOW_PAGE_PROCESSES "Processes"
#define MAIN_WINDOW_PAGE_PERFORMANCE "Performance"

MainWindow::MainWindow(const Glib::RefPtr<Gtk::Application>& application) {
    m_Application = application;

    auto display = Gdk::Display::get_default();
    auto monitor = display->get_primary_monitor();

    Gdk::Rectangle screenSize;
    monitor->get_workarea(screenSize);

    set_title("WSysMon");
    set_default_size(0, (int)((double)screenSize.get_height() * 0.6));
    set_position(Gtk::WIN_POS_CENTER);

    // Processes View
    m_ProcessView = new ProcessesView(this);
    m_MainStack.add(m_ProcessView->GetRootWidget(), MAIN_WINDOW_PAGE_PROCESSES, MAIN_WINDOW_PAGE_PROCESSES);

    // Performance View
    m_PerformanceView = new PerformanceView(this);
    m_MainStack.add(m_PerformanceView->GetRootWidget(), MAIN_WINDOW_PAGE_PERFORMANCE, MAIN_WINDOW_PAGE_PERFORMANCE);

    // Main Tabber
    m_MainTabber.set_stack(m_MainStack);
    m_MainStack.property_visible_child().signal_changed().connect([this] {
        OnTabChanged();
    });
    add(m_MainStack);

    // Header Bar
    m_HeaderBar.set_show_close_button(true);
    m_HeaderBar.set_custom_title(m_MainTabber);
    set_titlebar(m_HeaderBar);

    // Menu
    m_Application->add_action("mainView.about", [] {
        spdlog::debug("About");
    });
    Glib::ustring ui_info =
            "<interface>"
            "  <menu id='menu-mainOptionsMenu'>"
            "    <section>"
            "      <item>"
            "        <attribute name='label' translatable='yes'>About</attribute>"
            "        <attribute name='action'>app.mainView.about</attribute>"
            "      </item>"
            "    </section>"
            "  </menu>"
            "</interface>";

    auto builder = Gtk::Builder::create();
    builder->add_from_string(ui_info);

    auto object = builder->get_object("menu-mainOptionsMenu");
    auto gmenu = Glib::RefPtr<Gio::Menu>::cast_dynamic(object);
    m_OptionsMenu = Gtk::Menu(gmenu);

    m_MenuButton.set_menu(m_OptionsMenu);
    m_MenuButton.set_image_from_icon_name("open-menu-symbolic");
    //m_HeaderBar.pack_end(m_MenuButton);

    this->signal_show().connect(sigc::mem_fun(*this, &MainWindow::OnShown));
    show_all_children();
}

MainWindow::~MainWindow() {
    SAFE_DELETE(m_ProcessView);
    SAFE_DELETE(m_PerformanceView);
}

void MainWindow::OnShown() {
    m_ProcessView->OnShown();
}

void MainWindow::OnTabChanged() {
    auto currPage = m_MainStack.get_visible_child_name();
    if(currPage == MAIN_WINDOW_PAGE_PROCESSES) {
        m_ProcessView->OnShown();
        m_PerformanceView->OnHidden();
    } else if(currPage == MAIN_WINDOW_PAGE_PERFORMANCE) {
        m_PerformanceView->OnShown();
        m_ProcessView->OnHidden();
    }
}

Gtk::Application *MainWindow::GetApp() {
    return m_Application.get();
}
