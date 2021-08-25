#include "MainWindow.hpp"

namespace gtkmm
{
	MainWindow::MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
		: Gtk::Window(cobject)
	{
		//treeview
		Gtk::TreeView *tree;
		builder->get_widget("treeview", tree);
		this->treeview = std::unique_ptr<Gtk::TreeView>{tree};

		this->treemodel = std::make_unique<TreeModel>();
		this->treestore = Gtk::TreeStore::create(*this->treemodel);
		this->treeview->set_model(this->treestore);

		//treeview
		this->treeview->append_column("id", this->treemodel->id);
		this->treeview->append_column("message", this->treemodel->m_name);
		this->treeview->append_column("variable", this->treemodel->v_name);
		this->treeview->append_column("data", this->treemodel->data);
		this->treeview->append_column("phys-unit", this->treemodel->phys_unit);
		this->treeview->append_column("format", this->treemodel->id_type);
		this->treeview->append_column("interface", this->treemodel->interface);
		this->treeview->append_column("count", this->treemodel->count);
		this->treeview->append_column("cycle-time", this->treemodel->cycle_time);

		//listview
		Gtk::TreeView *list;
		builder->get_widget("listview", list);
		this->listview = std::unique_ptr<Gtk::TreeView>{list};

		this->listmodel = std::make_unique<ListModel>();
		this->liststore = Gtk::ListStore::create(*this->listmodel);
		this->listview->set_model(this->liststore);

		//listview
		this->listview->append_column("interface", this->listmodel->interface_name);
		this->listview->append_column_editable("active", this->listmodel->active);
		
		//start, stop, clear button
		Gtk::ToolButton *start;
		builder->get_widget("start_view", start);
		this->start_view = std::unique_ptr<Gtk::ToolButton>{start};

		Gtk::ToolButton *stop;
		builder->get_widget("stop_view", stop);
		this->stop_view = std::unique_ptr<Gtk::ToolButton>{stop};

		Gtk::ToolButton *clear;
		builder->get_widget("clear_store", clear);
		this->clear_store = std::unique_ptr<Gtk::ToolButton>{clear};

		//add, delete, refresh interface list
		Gtk::Button *add;
		builder->get_widget("add_interface", add);
		this->add_interface = std::unique_ptr<Gtk::Button>{add};

		Gtk::Button *del;
		builder->get_widget("delete_interface", del);
		this->delete_interface = std::unique_ptr<Gtk::Button>{del};

		Gtk::Button *refresh;
		builder->get_widget("refresh_interface", refresh);
		this->refresh_interface = std::unique_ptr<Gtk::Button>{refresh};

		Gtk::Entry *entry;
		builder->get_widget("interface_field", entry);
		this->interface_field = std::unique_ptr<Gtk::Entry>{entry};

		//menue entry
		Gtk::ImageMenuItem *open;
		builder->get_widget("open_file", open);
		this->open_file = std::unique_ptr<Gtk::ImageMenuItem>{open};

		Gtk::ImageMenuItem *open_add;
		builder->get_widget("open_add_file", open_add);
		this->open_add_file = std::unique_ptr<Gtk::ImageMenuItem>{open_add};
		
		Gtk::ImageMenuItem *close;
		builder->get_widget("close_window", close);
		this->close_window = std::unique_ptr<Gtk::ImageMenuItem>{close};

		Gtk::ImageMenuItem *op_dialog;
		builder->get_widget("open_dialog", op_dialog);
		this->open_about_dialog = std::unique_ptr<Gtk::ImageMenuItem>{op_dialog};

		//aboutdialog
		Gtk::AboutDialog *about;
		builder->get_widget("about_dialog", about);	
		this->about_dialog = std::unique_ptr<Gtk::AboutDialog>{about};	

		//register functions
		this->start_view->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_start_view));
		this->stop_view->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_stop_view));
		this->clear_store->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_clear_store));

		this->add_interface->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_add_interface));
		this->delete_interface->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_delete_interface));
		this->refresh_interface->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_refresh_interface));
	
		this->open_file->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::on_open_file));
		this->open_add_file->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::on_open_add_file));
		this->close_window->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::on_close_window));
		this->open_about_dialog->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::on_open_about_dialog));
	
		//set button
		this->stop_view->set_sensitive(false);

		//treeview
		// this->treeview->signal_row_activated().connect([&, this](const auto& path, const auto& column)
		// {
		// 	if(path)
		// 	{
		// 		std::cout << path.to_string() << std::endl;
		// 	}
		// });

		// this->treeview->set_activate_on_single_click(true);
	}

	void MainWindow::on_start_view()
	{
		this->start_view->set_sensitive(false);
		this->stop_view->set_sensitive(true);
		this->running = true;
		for(auto& iter : this->liststore->children())
		{
			auto row = *iter;
			if(row[this->listmodel->active])
			{
				std::thread{[&, this](std::string interface){
					bool run{true};
					can::linux_socket s{interface};
					while(run)
					{
						auto fr = s.receive();
						if(fr)
						{
							std::lock_guard<std::shared_timed_mutex> guard{this->frames_mutex};
							{
								auto iter = this->frames.find(fr->can_id());
								if(iter != this->frames.end())
								{
									auto& [f, i, c, t1, t2, b] = iter->second;
									f = *fr;
									c++;
									t1 = t2;
									t2 = hr_clock::now();
									b = true;
								}
								else
								{
									tuple_t tuple = std::make_tuple(*fr, interface, 1, hr_clock::now(), hr_clock::now(), true);
									this->frames.insert(std::make_pair(fr->can_id(), tuple));
								}
							}
						}

						{
							std::shared_lock<std::shared_timed_mutex> guard{this->running_mutex};
							run = this->running;
						}
					}	
				}, std::string{row[this->listmodel->interface_name]}}.detach();
			}
		}

		this->connection = Glib::signal_timeout().connect(sigc::mem_fun(*this, &MainWindow::on_timeout), 50);
	}

	void MainWindow::on_stop_view()
	{
		this->connection.disconnect();

		{
			std::lock_guard<std::shared_timed_mutex> guard{this->running_mutex};
			this->running = false;
		}
		
		this->start_view->set_sensitive(true);
		this->stop_view->set_sensitive(false);
	}

	void MainWindow::on_clear_store()
	{
		this->on_stop_view();
		{
			std::lock_guard<std::shared_timed_mutex> guard{this->frames_mutex};
			this->frames.clear();
			this->treestore->clear();
			this->rows_with_no_message.clear();
			this->rows_with_message.clear();
			this->rows_with_variable.clear();
		}
	}

	bool MainWindow::on_timeout()
	{
		std::shared_lock guard{this->frames_mutex};
		for(auto& iter : this->frames)
		{
			auto& [fr, i, c, t1, t2, active] = iter.second;
			if(active)
			{
				active = false;
				auto found_message = this->messages.find(fr.can_id());
				if(found_message != this->messages.end())
				{
					auto found_row_with_message = this->rows_with_message.find(fr.can_id());
					if(found_row_with_message != this->rows_with_message.end())
					{
						auto iter = found_row_with_message->second;

						if(fr.format() == can::frame::Format::Standard)
						{
							iter->set_value(this->treemodel->id_type, std::string{"Standard"});
						}
						else
						{
							iter->set_value(this->treemodel->id_type, std::string{"Extended"});
						}
						iter->set_value(this->treemodel->count, std::to_string(c));
						iter->set_value(this->treemodel->cycle_time, std::to_string(std::chrono::duration_cast<std::chrono::duration<uint32_t, std::ratio<1, 1000>>>(t2 - t1).count()));

						auto range = this->rows_with_variable.equal_range(fr.can_id());
						for(auto first = range.first; first != range.second && first != rows_with_variable.end(); ++first)
						{
							auto& [v, e, row_iter] = first->second;
							if(v)
							{
								auto intermediate = std::visit(can::to_intermediate{fr}, v->var());
								if(e)
								{
									auto string = std::visit(can::to_string{*e}, intermediate);
									row_iter->set_value(this->treemodel->data, string);
								}
								else
								{
									auto string = std::visit(can::to_string{}, intermediate);
									row_iter->set_value(this->treemodel->data, string);
								}
							}
						}						
					}
					else
					{
						auto message_iter = this->treestore->append();

						std::stringstream ss;
						ss << std::uppercase << std::hex << fr.can_id();
						
						message_iter->set_value(this->treemodel->id, ss.str());
						message_iter->set_value(this->treemodel->m_name, found_message->second.name());
						
						if(fr.format() == can::frame::Format::Standard)
						{
							message_iter->set_value(this->treemodel->id_type, std::string{"Standard"});
						}
						else
						{
							message_iter->set_value(this->treemodel->id_type, std::string{"Extended"});
						}

						message_iter->set_value(this->treemodel->interface, i);
						message_iter->set_value(this->treemodel->count, std::to_string(c));
						message_iter->set_value(this->treemodel->cycle_time, std::to_string(std::chrono::duration_cast<std::chrono::duration<uint32_t, std::ratio<1, 1000>>>(t2 - t1).count()));
						
						this->rows_with_message.insert(std::make_pair(fr.can_id(), message_iter));

						for(auto& var : found_message->second.variables())
						{
							Gtk::TreeModel::iterator variable_iter = this->treestore->append(message_iter->children());
							variable_iter->set_value(this->treemodel->v_name, var.second.name());
							variable_iter->set_value(this->treemodel->phys_unit, var.second.phys_unit());

							auto intermediate = std::visit(can::to_intermediate{fr}, var.second.var());
							auto found_enum = this->enums.find(var.second.enum_name());
							
							if(found_enum != this->enums.end())
							{
								auto string = std::visit(can::to_string{found_enum->second}, intermediate);
								variable_iter->set_value(this->treemodel->data, string);

								auto tuple = std::make_tuple(&var.second, &found_enum->second, variable_iter);
								this->rows_with_variable.insert(std::make_pair(fr.can_id(), tuple));
							}
							else
							{
								auto string = std::visit(can::to_string{}, intermediate);
								variable_iter->set_value(this->treemodel->data, string);

								auto tuple = std::make_tuple(&var.second, nullptr, variable_iter);
								this->rows_with_variable.insert(std::make_pair(fr.can_id(), tuple));
							}
						}
					}
				}
				else
				{
					//update row without message
					auto found_row_with_no_message = this->rows_with_no_message.find(fr.can_id());
					if(found_row_with_no_message != this->rows_with_no_message.end())
					{
						auto iter = found_row_with_no_message->second;
						std::stringstream data;
						for(uint8_t i = 0; i < fr.size(); ++i)
						{
							data << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << +fr[i].value_or(0) << " ";
						}

						if(fr.format() == can::frame::Format::Standard)
						{
							iter->set_value(this->treemodel->id_type, std::string{"Standard"});
						}
						else
						{
							iter->set_value(this->treemodel->id_type, std::string{"Extended"});
						}

						iter->set_value(this->treemodel->data, data.str());
						iter->set_value(this->treemodel->count, std::to_string(c));
						iter->set_value(this->treemodel->cycle_time, std::to_string(std::chrono::duration_cast<std::chrono::duration<uint32_t, std::ratio<1, 1000>>>(t2 - t1).count()));
					}
					//add iter to row with no message
					else
					{
						auto iter = this->treestore->append();
						
						std::stringstream ss;
						ss << std::uppercase << std::hex << fr.can_id();
						iter->set_value(this->treemodel->id, ss.str());

						std::stringstream data;
						for(uint8_t i = 0; i < fr.size(); ++i)
						{
							data << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << +fr[i].value_or(0) << " ";
						}
						iter->set_value(this->treemodel->data, data.str());

						if(fr.format() == can::frame::Format::Standard)
						{
							iter->set_value(this->treemodel->id_type, std::string{"Standard"});
						}
						else
						{
							iter->set_value(this->treemodel->id_type, std::string{"Extended"});
						}

						iter->set_value(this->treemodel->interface, i);
						iter->set_value(this->treemodel->count, std::to_string(c));
						iter->set_value(this->treemodel->cycle_time, std::to_string(std::chrono::duration_cast<std::chrono::duration<uint32_t, std::ratio<1, 1000>>>(t2 - t1).count()));

						this->rows_with_no_message.insert(std::make_pair(fr.can_id(), iter));
					}
				}
			}
		}

		return true;
	}

	void MainWindow::on_add_interface()
	{	
		std::string can_interface_name = this->interface_field->get_text();
		if(!can_interface_name.empty())
		{
			for(auto iter : this->liststore->children())
			{
				auto row = *iter;
				std::string name = row[this->listmodel->interface_name];
				if(name == can_interface_name)
					return;
			}

			auto row = *(this->liststore->append());
			row[this->listmodel->interface_name] = can_interface_name;
			row[this->listmodel->active] = false;
		}
	}

	void MainWindow::on_delete_interface()
	{
		auto selection 	= this->listview->get_selection();
		auto iter 		= selection->get_selected();

		if(iter)
		{
			this->liststore->erase(iter);
		}
	}

	void MainWindow::on_refresh_interface()
	{
		std::string ip_link_show = "ip link show";
		std::array<char, 128> buffer;
		std::string result;
		std::shared_ptr<FILE> pipe(popen(ip_link_show.c_str(), "r"), pclose);
		
		if (!pipe) 
			throw std::runtime_error("popen() failed!");

		while (!feof(pipe.get()))
		{
			if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
					result += buffer.data();
		}

		std::regex r{R"(\bv?can\d+\b)"};
		std::smatch match;

		do
		{
			if(std::regex_search(result, match, r))
			{
				for(const auto& i : match)
				{
					std::string t = i;
					auto row = *(this->liststore->append());
					row[this->listmodel->interface_name] = t;
					row[this->listmodel->active] = false;

				}
				result = match.suffix();
			}
			else
			{
				break;
			}

		}while(!match.empty());
	}

	void MainWindow::on_open_file()
	{
		try
		{
            Gtk::FileChooserDialog dialog("Chose a *.json file:");
            dialog.set_transient_for(*this);
            dialog.add_button("Abort", Gtk::RESPONSE_CLOSE);
            dialog.add_button("Select", Gtk::RESPONSE_OK);

            Glib::RefPtr<Gtk::FileFilter> f = Gtk::FileFilter::create();
            f->add_pattern("*.json");
            dialog.set_filter(f);
            dialog.run();

            auto file 	= dialog.get_file();
			auto path	= file->get_path();

			can::json json{path};

			this->messages 	= json.messages();
			this->enums 	= json.enums();               
		}
		catch(std::exception& e)
		{
			// this->error_label->set_text(e.what());
		}		
	}

	void MainWindow::on_open_add_file()
	{

	}

	void MainWindow::on_close_window()
	{
		this->hide();
	}

	void MainWindow::on_open_about_dialog()
	{
		this->about_dialog->run();
	}
}