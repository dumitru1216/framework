#include "../../inc.hh"
#pragma optimize("", off)

// unsafe shit
static int scroll[max_childs];
static bool scroll_moved[max_childs];
static float scroll_offset[max_childs];

gui::c_window::c_window(std::string title, math_wraper::c_vector_2d* position, const math_wraper::c_vector_2d& size)
{
	this->title = title;
	this->pos = position;
	this->size = size;

	// nah this will be totally dogshit
	// totally dogshit
	this->tab_pointer = std::make_shared<c_tab>();

	// drawing the window
	this->handle_input();
	this->think();
}

void gui::c_window::think()
{
	g_ctx->frame_alpha = g_modular->create_animation(this->title + "#frame_alpha", g_ctx->is_frame_open);
	if (g_ctx->frame_alpha <= 0.f)
		return;

}

void gui::c_window::handle_input()
{
	// frame open input
	if (ImGui::IsKeyPressed(ImGuiKey_Insert)) {
		g_ctx->is_frame_open = !g_ctx->is_frame_open;
	}

	// vars to store old data and mous edelta
	static math_wraper::c_vector_2d prev_mouse{};
	static math_wraper::c_vector_2d delta{};

	// init mouse delta
	delta = prev_mouse - input_wraper::get_mouse_position();

	if (!g_ctx->dragging && input_wraper::mouse_in_region(math_wraper::c_vector_2d(pos->x, pos->y), math_wraper::c_vector_2d(200, 30)) && input_wraper::key_down(VK_LBUTTON)) {
		g_ctx->dragging = true;
	}
	else if (g_ctx->dragging && input_wraper::key_down(VK_LBUTTON)) {
		*this->pos -= delta;
	}
	else if (g_ctx->dragging && !input_wraper::key_down(VK_LBUTTON)) {
		g_ctx->dragging = false;
	}

	// set prev
	prev_mouse = input_wraper::get_mouse_position();
}

void gui::c_window::create_page(const std::shared_ptr<c_page>& page)
{
	auto parent_pos = math_wraper::c_vector_2d(this->pos->x + 20, this->pos->y + 60);

	page->set_parent_position(parent_pos); // *this->pos
	page->post_initialization();
}

bool gui::c_window::is_opened()
{
	return g_ctx->is_frame_open;
}

static math_wraper::c_vector_2d pos = math_wraper::c_vector_2d(200, 200);
static math_wraper::c_vector_2d size = math_wraper::c_vector_2d(600, 500);

// 600 - 40 / 2

void gui::c_gui::initialize()
{
	auto window = std::make_shared<c_window>("window", &pos, size); {
		auto aimbot_tab = window->tab_pointer->add_tab(ICON_FA_GUN);
		if (aimbot_tab) {
			auto aim_subtab = window->tab_pointer->add_subtab("Aimbot");
			auto other_subtab = window->tab_pointer->add_subtab("Other");

			if (aim_subtab) {
				auto page1 = std::make_shared<c_page>("Page", math_wraper::c_vector_2d(0, 10), math_wraper::c_vector_2d(275, 300), 0); {
					window->create_page(page1);
					static bool a[3]{false};
					static float b[3]{ 0.f };
					static int c[3]{ 0 };

					static auto popup = std::make_shared<c_popup>("Popup", math_wraper::c_vector_2d(200, 200), 0);
					popup->assign_elements([&]() {
						auto checkbox = std::make_shared<c_checkbox>("Checkbox", &a[0]);
						auto checkbox2 = std::make_shared<c_checkbox>("Checkbox sec", &a[1]);
						auto slider_float = std::make_shared<c_slider_float>("Slider float", &b[0], 0.f, 100.f, L"%");
						auto slider_int = std::make_shared<c_slider_int>("Slider int", &c[0], 0, 100, L"%");

						auto combo = std::make_shared<c_combo>("Combo", &c[1], std::vector<std::string>{"None", "Selection 1"});
						auto multi_combo = std::make_shared<c_multi_combo>("Multi combo");

						// multicombo setup
						static bool ac[10]{ false };
						multi_combo->bind("Selectable 1", &ac[0]);
						multi_combo->bind("Selectable 2", &ac[1]);
						multi_combo->bind("Selectable 3", &ac[2]);
						multi_combo->bind("Selectable 4", &ac[4]);
						multi_combo->bind("Selectable 5", &ac[5]);

						auto button = std::make_shared<c_button>("Button", [&]() {});

						static color_var_t var{}, bos{};
						auto colorpicker = std::make_shared<c_colorpicker>("Colorpicker", &var);
						auto colorpicker2 = std::make_shared<c_colorpicker>("Colorpicker 2", &bos);

						//popup->bind(colorpicker); // this doesnt work
						popup->bind(checkbox);
						//popup->bind(colorpicker2);
						popup->bind(checkbox2);
						popup->bind(slider_float);
						popup->bind(slider_int);
						popup->bind(combo);
						popup->bind(multi_combo);
						popup->bind(button);

						popup->prioritize_layer(combo);
						popup->prioritize_layer(multi_combo);
						//popup->prioritize_layer(colorpicker);
						//popup->prioritize_layer(colorpicker2);

						popup->scrolling();
					});

					static auto popup2 = std::make_shared<c_popup>("Popup second", math_wraper::c_vector_2d(200, 200), 1);

					auto checkbox = std::make_shared<c_checkbox>("Checkbox", &a[0]);

					static std::string str;
					auto textinput = std::make_shared<c_textinput>("Text input", &str);

					auto checkbox2 = std::make_shared<c_checkbox>("Checkbox second", &a[1]);
					auto checkbox3 = std::make_shared<c_checkbox>("Checkbox 3", &a[2]);
					auto slider_float = std::make_shared<c_slider_float>("Slider float", &b[0], 0.f, 100.f, L"%");
					auto slider_int = std::make_shared<c_slider_int>("Slider int", &c[0], 0, 100, L"%");

					auto combo = std::make_shared<c_combo>("Combo", &c[1], std::vector<std::string>{"None", "Selection 1"});
					auto multi_combo = std::make_shared<c_multi_combo>("Multi combo");
					auto button = std::make_shared<c_button>("Button", [&]() {});

					static key_var_t keybind_var{}, inlined_two{}, inlined_three{};
					auto keybind = std::make_shared<c_keybind>("Keybind", &keybind_var);
					auto keybind2 = std::make_shared<c_keybind>("Keybind 2", &inlined_two);
					auto keybind3 = std::make_shared<c_keybind>("Keybind 3", &inlined_three);
					keybind2->set_inlined(true, 0);
					keybind3->set_inlined(true, 27);					

					static color_var_t var{}, bos{};
					auto colorpicker = std::make_shared<c_colorpicker>("Colorpicker", &var);
					colorpicker->set_inlined(true, 0);

					auto colorpicker2 = std::make_shared<c_colorpicker>("Colorpicker 2", &bos);

					page1->bind(textinput);
					page1->bind(popup);
					page1->bind(colorpicker);
					page1->bind(keybind3);
					page1->bind(checkbox);

					//page1->bind(keybind2);
					page1->bind(colorpicker2);
					page1->bind(checkbox2);

					page1->bind(keybind);
					page1->bind(checkbox3);
					page1->bind(slider_float);
					page1->bind(slider_int);
					page1->bind(combo);

					// multicombo setup
					static bool ac[10]{ false };
					multi_combo->bind("Selectable 1", &ac[0]);
					multi_combo->bind("Selectable 2", &ac[1]);
					multi_combo->bind("Selectable 3", &ac[2]);
					multi_combo->bind("Selectable 4", &ac[4]);
					multi_combo->bind("Selectable 5", &ac[5]);

					// now bind the element
					page1->bind(multi_combo);
					page1->bind(button);
					page1->bind(checkbox2);

					if (keybind_var.active()) {
						printf("Keybind on hold\n");
					}

					page1->scrolling();
					page1->clear_instance();
				}

				auto page2 = std::make_shared<c_page>("Page 2", math_wraper::c_vector_2d(0, 10 + 312), math_wraper::c_vector_2d(275, 100), 1); {
					window->create_page(page2);

					static bool b = false;
					auto checkbox = std::make_shared<c_checkbox>("Checkbox", &b);
					page2->bind(checkbox);
					page2->clear_instance();
				}

				auto page3 = std::make_shared<c_page>("Page 3 - Scrolling", math_wraper::c_vector_2d(287, 10), math_wraper::c_vector_2d(275, 412), 2); {
					window->create_page(page3);

					static int a = 0;
					auto listbox = std::make_shared<c_listbox>("Listbox", &a, std::vector<std::string>{"None", "Dragonfire 1", "Dragonfire 2", "Dragonfire 3", "Dragonfire 4", "Dragonfire 5", "Dragonfire 6", "Dragonfire 7", "Dragonfire 8", "Dragonfire 9", "Dragonfire 10", "Dragonfire 11", "Dragonfire 12", "Dragonfire 13", "Dragonfire 14"});
					page3->bind(listbox);

			
					page3->scrolling();
					page3->clear_instance();
				}
			}

			if (other_subtab) {

			}
		}

		auto players_tab = window->tab_pointer->add_tab(ICON_FA_USERS);
		if (players_tab) {

		}

		auto visuals_tab = window->tab_pointer->add_tab(ICON_FA_BULLSEYE);
		if (visuals_tab) {

		}

		auto misc_tab = window->tab_pointer->add_tab(ICON_FA_GEAR);
		if (misc_tab) {

		}

		auto config_tab = window->tab_pointer->add_tab(ICON_FA_FILE);
		if (config_tab) {

		}
	}

}

bool gui::c_tab::add_tab(std::string tab_string)
{
	// we push first
	g_ctx->tabs.push_back(tab_string.data());

	// set current tab
	g_ctx->cur_tab = tab_string;

	// check if the tab is active
	return (g_ctx->active_tab == g_ctx->tabs.size() - 1);
}

bool gui::c_tab::add_subtab(std::string subtab_string)
{
	// we push the subtab first
	g_ctx->sub_tabs.push_back(subtab_string.data());
	
	// set current tab
	g_ctx->cur_subtab = subtab_string;

	// check if its active
	return (g_ctx->active_subtab == g_ctx->sub_tabs.size() - 1);
}

gui::c_page::c_page(std::string title, math_wraper::c_vector_2d position, math_wraper::c_vector_2d size, int id)
{
	this->title = title;
	this->pos = position;
	this->size = size;
	this->id = id;
}

void gui::c_page::think()
{
	
}

void gui::c_page::post_initialization()
{
	// set layout
	this->layout.x = this->get_parent_pos().x;
	this->layout.y[this->id] = this->get_parent_pos().y + scroll[this->id];

	// reset offset
	scroll_offset[this->id] = 0.f;

	// page frame hovering
	this->hovered = input_wraper::frame_from_region(this->pos, this->size) && !g_ctx->block_input;

	// run child
	this->think();

	// adjust limit
	// clip if needed
	framework::draw->push_draw_limit(this->pos + math_wraper::c_vector_2d(0, 38), this->size - math_wraper::c_vector_2d(0, 40));
}

void gui::c_page::clear_instance()
{
	// restore if we did clip
	framework::draw->restore_draw_limit();
}

void gui::c_page::scrolling()
{
	g_profiler->add_to_profiler("block: " + std::to_string(g_ctx->block_input));
	g_profiler->add_to_profiler("scroll offset: " + std::to_string(scroll_offset[this->id]));
	g_profiler->add_to_profiler("scroll: " + std::to_string(scroll[this->id]));
	g_profiler->add_to_profiler("page safe area: " + std::to_string(this->size.y - 40));

	// check if input is blocked and if the scrolling area is lower than the child size
	if (g_ctx->block_input || scroll_offset[this->id] <= this->size.y - 40 || !this->hovered)
		return;

	const float header_height = 30.f;
	const float margin = 5.f;
	const float scrollbar_width = 4.f;
	const float safe_area = this->size.y - 40;

	float content_height = scroll_offset[this->id]; // total elements height
	float viewable_height = this->size.y - header_height - margin;

	float scrollable_height = content_height - viewable_height;
	float scroll_ratio = -(float)scroll[this->id] / scrollable_height;
	scroll_ratio = std::clamp(scroll_ratio, 0.f, 1.f);

	float thumb_height = viewable_height * (viewable_height / content_height);
	float thumb_y = this->pos.y + header_height + 2 + scroll_ratio * (viewable_height - thumb_height);

	math_wraper::c_vector_2d track_pos = math_wraper::c_vector_2d(this->pos.x + this->size.x - margin - scrollbar_width, this->pos.y + header_height + 2);
	math_wraper::c_vector_2d track_size = math_wraper::c_vector_2d(scrollbar_width, viewable_height);

	math_wraper::c_vector_2d thumb_pos = math_wraper::c_vector_2d(track_pos.x, thumb_y);
	math_wraper::c_vector_2d thumb_size = math_wraper::c_vector_2d(scrollbar_width, thumb_height);

	framework::draw->rect_filled(track_pos, track_size, g_theme->scroll_thumb, 2);
	framework::draw->rect_filled(thumb_pos, thumb_size, g_theme->scroll_track, 2);

	if (input_wraper::mouse_wheel() > 0) {
		scroll[this->id] += 30;
	}
	else if (input_wraper::mouse_wheel() < 0) {
		scroll[this->id] -= 30;
	}

	// prevent over scrolling
	const float max_scroll = content_height - safe_area;
	scroll[this->id] = std::clamp((float)scroll[this->id], -max_scroll, 0.f);
}

void gui::c_page::set_parent_position(math_wraper::c_vector_2d pos)
{
	this->pos += pos;
}

int gui::c_page::get_parent_elemnt(page_elements_t element)
{
	if (element == page_elements_t::checkbox)
		return page_elements_t::checkbox;
	else if (element == page_elements_t::slider)
		return page_elements_t::slider;
	else if (element == page_elements_t::dropdown)
		return page_elements_t::dropdown;
	else if (element == page_elements_t::button)
		return page_elements_t::button;
	else // no element or just a fuckin error, just return 0
		return 0;
}

// get child parent pos, ussualy used for element identation
math_wraper::c_vector_2d gui::c_page::get_parent_pos()
{
	return this->pos + math_wraper::c_vector_2d(15, 40);
}

// bind checkbox element
void gui::c_page::bind(const std::shared_ptr<c_checkbox>& element)
{
	// set parent child
	g_ctx->parent_child = this->title;

	element->pos = {this->layout.x, this->layout.y[this->id]};
	element->think();

	// input handler
	element->handle_input();

	// space between elements
	this->layout.y[this->id] += this->get_parent_elemnt(page_elements_t::checkbox) + element_spacing;
	scroll_offset[this->id] += this->get_parent_elemnt(page_elements_t::checkbox) + element_spacing;
}

void gui::c_page::bind(const std::shared_ptr<c_slider_float>& element) 
{
	// set parent child
	g_ctx->parent_child = this->title;
	g_ctx->parent_width = this->size.x - 30;

	element->pos = { this->layout.x, this->layout.y[this->id] };
	element->think();

	// input handler
	element->handle_input();

	// space between elements
	this->layout.y[this->id] += this->get_parent_elemnt(page_elements_t::slider) + element_spacing;
	scroll_offset[this->id] += this->get_parent_elemnt(page_elements_t::slider) + element_spacing;
}

void gui::c_page::bind(const std::shared_ptr<c_slider_int>& element)
{
	// set parent child
	g_ctx->parent_child = this->title;
	g_ctx->parent_width = this->size.x - 30;

	element->pos = { this->layout.x, this->layout.y[this->id] };
	element->think();

	// input handler
	element->handle_input();

	// space between elements
	this->layout.y[this->id] += this->get_parent_elemnt(page_elements_t::slider) + element_spacing;
	scroll_offset[this->id] += this->get_parent_elemnt(page_elements_t::slider) + element_spacing;
}

void gui::c_page::bind(const std::shared_ptr<c_combo>& element)
{
	// set parent child
	g_ctx->parent_child = this->title;
	g_ctx->parent_width = this->size.x - 30;

	element->pos = { this->layout.x, this->layout.y[this->id] };
	element->think();
	element->think_new_layer();

	// input handler
	element->handle_input();

	// space between elements
	this->layout.y[this->id] += this->get_parent_elemnt(page_elements_t::dropdown) + element_spacing;
	scroll_offset[this->id] += this->get_parent_elemnt(page_elements_t::dropdown) + element_spacing;
}

void gui::c_page::bind(const std::shared_ptr<c_textinput>& element)
{
	// set parent child
	g_ctx->parent_child = this->title;
	g_ctx->parent_width = this->size.x - 30;

	element->pos = { this->layout.x, this->layout.y[this->id] };
	element->think();

	// input handler
	element->handle_input();

	// space between elements
	this->layout.y[this->id] += this->get_parent_elemnt(page_elements_t::dropdown) + element_spacing;
	scroll_offset[this->id] += this->get_parent_elemnt(page_elements_t::dropdown) + element_spacing;
}

void gui::c_page::bind(const std::shared_ptr<c_multi_combo>& element)
{
	// set parent child
	g_ctx->parent_child = this->title;
	g_ctx->parent_width = this->size.x - 30;

	element->pos = { this->layout.x, this->layout.y[this->id] };
	element->think();
	element->think_new_layer();

	// input handler
	element->handle_input();

	// space between elements
	this->layout.y[this->id] += this->get_parent_elemnt(page_elements_t::dropdown) + element_spacing;
	scroll_offset[this->id] += this->get_parent_elemnt(page_elements_t::dropdown) + element_spacing;
}

void gui::c_page::bind(const std::shared_ptr<c_button>& element)
{
	// set parent child
	g_ctx->parent_child = this->title;
	g_ctx->parent_width = this->size.x - 30;

	element->pos = { this->layout.x, this->layout.y[this->id] };
	element->think();

	// input handler
	element->handle_input();

	// space between elements
	this->layout.y[this->id] += this->get_parent_elemnt(page_elements_t::button) + element_spacing;
	scroll_offset[this->id] += this->get_parent_elemnt(page_elements_t::button) + element_spacing;
}

void gui::c_page::bind(const std::shared_ptr<c_listbox>& element)
{
	// set parent child
	g_ctx->parent_child = this->title;
	g_ctx->parent_width = this->size.x - 30;

	element->pos = { this->layout.x, this->layout.y[this->id] };

	// input handler
	element->handle_input();

	element->think();

	// space between elements
	this->layout.y[this->id] += this->get_parent_elemnt(page_elements_t::button) + element_spacing;
	scroll_offset[this->id] += this->get_parent_elemnt(page_elements_t::button) + element_spacing;
}

void gui::c_page::bind(const std::shared_ptr<c_popup>& element)
{
	// set parent child
	g_ctx->parent_child = this->title;
	g_ctx->parent_width = this->size.x - 30;

	element->pos = { this->layout.x + g_ctx->parent_width - 20, this->layout.y[this->id] };

	// input handler
	element->handle_input();
	element->post_initialization();
}

void gui::c_page::bind(const std::shared_ptr<c_colorpicker>& element)
{
	// set parent child
	g_ctx->parent_child = this->title;
	g_ctx->parent_width = this->size.x - 30;

	element->pos = { this->layout.x + (g_ctx->parent_width - 20) - (element->inlined ? (25 + element->parent_space) : 0), this->layout.y[this->id] };

	// input handler
	element->handle_input();
	element->think();
	element->think_new_layer();
}

void gui::c_page::bind(const std::shared_ptr<c_keybind>& element)
{
	// set parent child
	g_ctx->parent_child = this->title;
	g_ctx->parent_width = this->size.x - 30;

	element->pos = { this->layout.x + (g_ctx->parent_width - 20) - (element->inlined ? (25 + element->parent_space) : 0), this->layout.y[this->id] };

	// input handler
	element->handle_input();
	element->think();
	element->think_new_layer();
}

gui::c_checkbox::c_checkbox(std::string label, bool* value)
{
	this->label = label;
	this->value = value;
}

void gui::c_checkbox::think() 	
// printf("parent child: %s:%s\n", this->label.c_str(), g_ctx->parent_child.c_str());
{
	
}

void gui::c_checkbox::handle_input(bool is_popup)
{
	// do input handler
	if (!is_popup) {
		if (g_ctx->block_input)
			return; // do not run if we block the input
	}

	if (input_wraper::mouse_in_region(math_wraper::c_vector_2d(this->pos.x, this->pos.y), math_wraper::c_vector_2d(18, 18)) && input_wraper::mouse_clicked(ImGuiMouseButton_Left)) {
		*this->value = !*this->value;
	}
}

gui::c_slider_float::c_slider_float(std::string title, float* val, float min, float max, std::wstring suf)
{
	this->title = title;
	this->value = val;
	this->min = min;
	this->max = max;
	this->suf = suf;
}

void gui::c_slider_float::think()
{
	
}

void gui::c_slider_float::handle_input(bool is_popup)
{
	// do input handler
	if (!is_popup) {
		if (g_ctx->block_input)
			return; // do not run if we block the input
	}

	// get active object id
	size_t active_object = g_modular->hash(this->title + g_ctx->parent_child);

	// get frame
	this->hovered = input_wraper::frame_from_region(math_wraper::c_vector_2d(this->pos.x, this->pos.y + framework::fonts->poppins_regular.measure(this->title).y + 5), math_wraper::c_vector_2d(g_ctx->parent_width, 10));
	bool clicked = this->hovered && input_wraper::mouse_clicked(ImGuiMouseButton_Left);

	printf("g_ctx->active_object: %llu, active_object: %llu\n",
		(unsigned long long)g_ctx->active_object,
		(unsigned long long)active_object);


	if (g_ctx->active_object == 0 && clicked) {
		g_ctx->active_object = active_object;
		printf("Set active_object to: %d\n", active_object);
	}

	if (g_ctx->active_object == active_object) {
		printf("Handling input for active_object: %d\n", active_object);
		if (input_wraper::mouse_down(ImGuiMouseButton_Left)) {
			printf("Mouse is down, processing input...\n");
			// Process input
		}
		else {
			printf("Mouse is not down, resetting active_object.\n");
			g_ctx->active_object = 0;
		}
	}

}

gui::c_slider_int::c_slider_int(std::string title, int* val, int min, int max, std::wstring suf)
{
	this->title = title;
	this->value = val;
	//*this->animated_value = 0.f; // convert it to float
	this->min = min;
	this->max = max;
	this->suf = suf;
}

void gui::c_slider_int::think()
{
	
}

void gui::c_slider_int::handle_input(bool is_popup)
{
	// do input handler
	if (!is_popup) {
		if (g_ctx->block_input)
			return; // do not run if we block the input
	}

	// get active object id
	size_t active_object = g_modular->hash(this->title + g_ctx->parent_child);

	// get frame
	this->hovered = input_wraper::frame_from_region(math_wraper::c_vector_2d(this->pos.x, this->pos.y + framework::fonts->poppins_regular.measure(this->title).y + 5), math_wraper::c_vector_2d(g_ctx->parent_width, 10));
	bool clicked = this->hovered && input_wraper::mouse_clicked(ImGuiMouseButton_Left);

	if (g_ctx->active_object == 0) // there are no elements that are active and if we clicked
	{
		if (clicked) // set the global active object var to this object
		{
			g_ctx->active_object = active_object;

			// debugging
			// printf("[c_slider_float::handle_input] sent input\n");
		}
	}
	else if (g_ctx->active_object == active_object) { // this is the object we are sending input to
		if (input_wraper::mouse_down(ImGuiMouseButton_Left)) {
			float offset = std::clamp<float>(
				math_wraper::c_vector_2d(input_wraper::get_mouse_position() - this->pos).x,
				0.f,
				(float)g_ctx->parent_width
			);

			float target = g_modular->modulate_float(offset, 0.f, (float)g_ctx->parent_width, (float)this->min, (float)this->max);

			static float current = (float)(*this->value);
			current += (target - current) * 0.1f;

			// rounding
			*this->value = (int)(current + 0.5f);

			// snap it for precision
			if (std::abs(current - target) < 0.5f)
				*this->value = (int)(target + 0.5f);
		}
		else {
			g_ctx->active_object = 0;
		}
	}
}

gui::c_combo::c_combo(std::string title, int* val, std::vector<std::string> items)
{
	this->title = title;
	this->val = val;
	this->items = items;
}

void gui::c_combo::think()
{
	
}

void gui::c_combo::think_new_layer()
{
	
}

//
void gui::c_combo::handle_input(bool is_popup)
{
	// do input handler
	if (!is_popup) {
		if (g_ctx->block_input)
			return; // do not run if we block the input
	}

	// get active object id
	size_t active_object = g_modular->hash(this->title + g_ctx->parent_child);

	// get frame
	this->hovered = input_wraper::frame_from_region(math_wraper::c_vector_2d(this->pos.x, this->pos.y + framework::fonts->poppins_regular.measure(this->title).y + 5), math_wraper::c_vector_2d(g_ctx->parent_width, 26));
	bool clicked = this->hovered && input_wraper::mouse_clicked(ImGuiMouseButton_Left);

	if (g_ctx->active_object == 0) // there are no elements that are active and if we clicked
	{
		if (clicked) // set the global active object var to this object
		{
			g_ctx->active_object = active_object;

			// debugging
			// printf("[c_slider_float::handle_input] sent input\n");
		}
	}
}

gui::c_multi_combo::c_multi_combo(std::string title)
{
	this->title = title;
}

void gui::c_multi_combo::bind(std::string title, bool* var)
{
	// push item
	this->items.push_back(c_combo_context(title, var));
}

void gui::c_multi_combo::think()
{
	

}

void gui::c_multi_combo::think_new_layer()
{
	
}

void gui::c_multi_combo::handle_input(bool is_popup)
{
	// do input handler
	if (!is_popup) {
		if (g_ctx->block_input)
			return; // do not run if we block the input
	}

	// get active object id
	size_t active_object = g_modular->hash(this->title + g_ctx->parent_child);

	// get frame
	this->hovered = input_wraper::frame_from_region(math_wraper::c_vector_2d(this->pos.x, this->pos.y + framework::fonts->poppins_regular.measure(this->title).y + 5), math_wraper::c_vector_2d(g_ctx->parent_width, 26));
	bool clicked = this->hovered && input_wraper::mouse_clicked(ImGuiMouseButton_Left);

	if (g_ctx->active_object == 0) // there are no elements that are active and if we clicked
	{
		if (clicked) // set the global active object var to this object
		{
			g_ctx->active_object = active_object;

			// debugging
			// printf("[c_slider_float::handle_input] sent input\n");
		}
	}
}

gui::c_button::c_button(std::string title, std::function<void()> fn)
{
	this->title = title;
	this->fn = fn;
}

struct circle_t {
	math_wraper::c_vector_2d pos{};
	float alpha = 1.f;
	float radius = 0.f;
	float fade_speed = 0.02f;
};

static std::vector<circle_t> circles{};

void gui::c_button::think()
{
	
}

void gui::c_button::handle_input(bool is_popup)
{
	// do input handler
	if (!is_popup) {
		if (g_ctx->block_input)
			return; // do not run if we block the input
	}

	// get active object id
	size_t active_object = g_modular->hash(this->title + g_ctx->parent_child);

	// get frame
	this->hovered = input_wraper::frame_from_region(math_wraper::c_vector_2d(this->pos.x, this->pos.y), math_wraper::c_vector_2d(g_ctx->parent_width, 26));
	bool clicked = this->hovered && input_wraper::mouse_clicked(ImGuiMouseButton_Left);

	if (g_ctx->active_object == 0) // there are no elements that are active and if we clicked
	{
		if (clicked) // set the global active object var to this object
		{
			g_ctx->active_object = active_object;

			// debugging
			// printf("[c_slider_float::handle_input] sent input\n");
		}
	}
	else if (g_ctx->active_object == active_object)
	{
		circles.push_back({ input_wraper::get_mouse_position() });

		// invoke function
		fn();
		g_ctx->active_object = 0; // reset so it wont invoke again
	}
}

gui::c_listbox::c_listbox(std::string title, int* val, std::vector<std::string> items)
{
	this->title = title;
	this->val = val;
	this->items = items;
}

void gui::c_listbox::think()
{
	
}

void gui::c_listbox::handle_input()
{
	// do input handler
	if (g_ctx->block_input && !g_ctx->is_popup)
		return; // do not run if we block the input

	// get active object id
	size_t active_object = g_modular->hash(this->title + g_ctx->parent_child);

	// get frame
	this->hovered = input_wraper::frame_from_region(math_wraper::c_vector_2d(this->pos.x, this->pos.y + framework::fonts->poppins_regular.measure(this->title).y + 5), math_wraper::c_vector_2d(g_ctx->parent_width, this->height));
}

// if u want to override the height just set the flag
void gui::c_listbox::set_height(int height)
{
	this->height = height;
}

gui::c_popup::c_popup(std::string title, math_wraper::c_vector_2d size, int id)
{
	this->title = title;
	this->size = size;
	this->id = id; // we will use this for scrolling or other array vars
}

// get parent pos
math_wraper::c_vector_2d gui::c_popup::get_parent_pos()
{
	return this->pos + math_wraper::c_vector_2d(15, 40);
}

int gui::c_popup::get_parent_elemnt(page_elements_t element)
{
	if (element == page_elements_t::checkbox)
		return page_elements_t::checkbox;
	else if (element == page_elements_t::slider)
		return page_elements_t::slider;
	else if (element == page_elements_t::dropdown)
		return page_elements_t::dropdown;
	else if (element == page_elements_t::button)
		return page_elements_t::button;
	else // no element or just a fuckin error, just return 0
		return 0;
}

framework::anim_context_t scrll_offset{}, scrll{}, scrll_moved{};

void gui::c_popup::scrolling()
{	
	// check if input is blocked and if the scrolling area is lower than the child size
	if (g_ctx->block_input && !g_ctx->is_popup || scrll_offset.m_value <= this->size.y - 40 || !this->hovered_page)
		return;

	const float header_height = 30.f;
	const float margin = 5.f;
	const float scrollbar_width = 4.f;
	const float safe_area = this->size.y - 40;

	float content_height = scrll_offset.m_value; // total elements height
	float viewable_height = this->size.y - header_height - margin;

	float scrollable_height = content_height - viewable_height;
	float scroll_ratio = -(float)scrll.m_value / scrollable_height;
	scroll_ratio = std::clamp(scroll_ratio, 0.f, 1.f);

	float thumb_height = viewable_height * (viewable_height / content_height);
	float thumb_y = this->pos.y + header_height + 2 + scroll_ratio * (viewable_height - thumb_height);

	math_wraper::c_vector_2d track_pos = math_wraper::c_vector_2d(this->pos.x + this->size.x - margin - scrollbar_width, this->pos.y + header_height + 2);
	math_wraper::c_vector_2d track_size = math_wraper::c_vector_2d(scrollbar_width, viewable_height);

	math_wraper::c_vector_2d thumb_pos = math_wraper::c_vector_2d(track_pos.x, thumb_y);
	math_wraper::c_vector_2d thumb_size = math_wraper::c_vector_2d(scrollbar_width, thumb_height);

	framework::draw->rect_filled(track_pos, track_size, g_theme->scroll_thumb, 2);
	framework::draw->rect_filled(thumb_pos, thumb_size, g_theme->scroll_track, 2);

	if (input_wraper::mouse_wheel() > 0) {
		scrll.m_value += 30;
	}
	else if (input_wraper::mouse_wheel() < 0) {
		scrll.m_value -= 30;
	}

	// prevent over scrolling
	const float max_scroll = content_height - safe_area;
	scrll.m_value = std::clamp((float)scrll.m_value, -max_scroll, 0.f);
}

// initialie this when we bind the element
void gui::c_popup::post_initialization()
{
	// reset this
	scrll_offset.m_value = 0.f;

	// initialize scroll mmebers
	if (!g_ctx->initialized_stack_members) {
		scrll_offset = framework::g_anim_base.build(this->title + "#scrll_offset");
		scrll = framework::g_anim_base.build(this->title + "#scrll");
		scrll_moved = framework::g_anim_base.build(this->title + "#scrll_moved");

		g_ctx->initialized_stack_members = true;
	}

	// set layout
	this->layout.x = this->get_parent_pos().x;
	this->layout.y[this->id] = this->get_parent_pos().y + scrll.m_value;

	// page frame hovering
	this->hovered_page = input_wraper::frame_from_region(this->pos, this->size) && !g_ctx->block_input;

	// run child
	this->think();
}

void gui::c_popup::think()
{
	// adjust limit
		//framework::draw->push_draw_limit(this->pos + math_wraper::c_vector_2d(0, 38), this->size - math_wraper::c_vector_2d(0, 40));
		//if (this->elements_backend != nullptr)
			//this->elements_backend(); // run the elements we bound to the popup

		// restore if we did clip
		//framework::draw->restore_draw_limit();

		//framework::globals::m_draw_list = ImGui::GetBackgroundDrawList();
}

void gui::c_popup::handle_input()
{
	// do input handler
	if (g_ctx->block_input || g_ctx->is_colorpicker)
		return; // do not run if we block the input

	// get active object id
	size_t active_object = g_modular->hash(this->title + g_ctx->parent_child);

	// get frame
	this->hovered = input_wraper::frame_from_region(math_wraper::c_vector_2d(this->pos.x, this->pos.y), math_wraper::c_vector_2d(14, 14));
	bool clicked = this->hovered && input_wraper::mouse_clicked(ImGuiMouseButton_Left);

	if (g_ctx->active_popup == 0) // there are no elements that are active and if we clicked
	{
		//g_ctx->is_popup = false;

		if (clicked) // set the global active object var to this object
		{
			g_ctx->block_input = true;
			g_ctx->active_popup = active_object;

			// debugging
			// printf("[c_slider_float::handle_input] sent input\n");
		}
	}
}

void gui::c_popup::assign_elements(std::function<void()> elements_backend)
{
	this->elements_backend = elements_backend;
}

void gui::c_popup::bind(const std::shared_ptr<c_checkbox>& element)
{
	// set parent child
	g_ctx->parent_child = this->title + "#popup";

	element->pos = { this->layout.x, this->layout.y[this->id] };
	element->think();

	// input handler
	element->handle_input(true);

	// space between elements
	this->layout.y[this->id] += this->get_parent_elemnt(page_elements_t::checkbox) + element_spacing;
	scrll_offset.m_value += this->get_parent_elemnt(page_elements_t::checkbox) + element_spacing;
}

void gui::c_popup::prioritize_layer(const std::shared_ptr<c_combo>& element)
{
	element->think_new_layer();

	if (element->opened)
		scrll_offset.m_value += element->height;
}

void gui::c_popup::prioritize_layer(const std::shared_ptr<c_colorpicker>& element)
{
	element->think_new_layer();

	// if (element->opened)
	// 	scrll_offset.m_value += element->height;
}

void gui::c_popup::prioritize_layer(const std::shared_ptr<c_multi_combo>& element)
{
	element->think_new_layer();

	if (element->opened)
		scrll_offset.m_value += element->height;
}

void gui::c_popup::bind(const std::shared_ptr<c_slider_float>& element)
{
	// set parent child
	g_ctx->parent_child = this->title;
	g_ctx->parent_width = this->size.x - 30;

	element->pos = { this->layout.x, this->layout.y[this->id] };

	// input handler
	element->handle_input(true);
	element->think();

	// space between elements
	this->layout.y[this->id] += this->get_parent_elemnt(page_elements_t::slider) + element_spacing;
	scrll_offset.m_value += this->get_parent_elemnt(page_elements_t::slider) + element_spacing;
}

void gui::c_popup::bind(const std::shared_ptr<c_slider_int>& element)
{
	// set parent child
	g_ctx->parent_child = this->title;
	g_ctx->parent_width = this->size.x - 30;

	element->pos = { this->layout.x, this->layout.y[this->id] };
	element->think();

	// input handler
	element->handle_input(true);

	// space between elements
	this->layout.y[this->id] += this->get_parent_elemnt(page_elements_t::slider) + element_spacing;
	scrll_offset.m_value += this->get_parent_elemnt(page_elements_t::slider) + element_spacing;
}

void gui::c_popup::bind(const std::shared_ptr<c_combo>& element)
{
	// set parent child
	g_ctx->parent_child = this->title;
	g_ctx->parent_width = this->size.x - 30;

	element->pos = { this->layout.x, this->layout.y[this->id] };
	element->think();

	// input handler
	element->handle_input(true);

	// space between elements
	this->layout.y[this->id] += this->get_parent_elemnt(page_elements_t::dropdown) + element_spacing;
	scrll_offset.m_value += this->get_parent_elemnt(page_elements_t::dropdown) + element_spacing;
}

void gui::c_popup::bind(const std::shared_ptr<c_multi_combo>& element)
{
	// set parent child
	g_ctx->parent_child = this->title;
	g_ctx->parent_width = this->size.x - 30;

	element->pos = { this->layout.x, this->layout.y[this->id] };
	element->think();

	// input handler
	element->handle_input(true);

	// space between elements
	this->layout.y[this->id] += this->get_parent_elemnt(page_elements_t::dropdown) + element_spacing;
	scrll_offset.m_value += this->get_parent_elemnt(page_elements_t::dropdown) + element_spacing;
}

void gui::c_popup::bind(const std::shared_ptr<c_button>& element)
{
	// set parent child
	g_ctx->parent_child = this->title;
	g_ctx->parent_width = this->size.x - 30;

	element->pos = { this->layout.x, this->layout.y[this->id] };
	element->think();

	// input handler
	element->handle_input(true);

	// space between elements
	this->layout.y[this->id] += this->get_parent_elemnt(page_elements_t::button) + element_spacing;
	scrll_offset.m_value += this->get_parent_elemnt(page_elements_t::button) + element_spacing;
}

void gui::c_popup::bind(const std::shared_ptr<c_colorpicker>& element)
{
	// set parent child
	g_ctx->parent_child = this->title;
	g_ctx->parent_width = this->size.x - 30;

	element->pos = { this->layout.x + (g_ctx->parent_width - 20) - (element->inlined ? (25 + element->parent_space) : 0), this->layout.y[this->id] };

	// input handler
	element->handle_input(true);
	element->think();
}

void gui::c_popup::clear_instance()
{
	// restore if we did clip
	framework::draw->restore_draw_limit();
}

gui::c_colorpicker::c_colorpicker(std::string title, color_var_t* color)
{
	this->title = title;
	this->var = color;

	HSV new_color = rgb_to_hsv({ (double)((float)this->var->color.r / 255.f),(double)
				   ((float)this->var->color.g / 255.f),(double)((float)this->var->color.b / 255.f) });

	this->cursor_pos.x = (float)new_color.s * 190.f;
	this->cursor_pos.y = 140.f - ((float)new_color.v * 140.f);
}

void gui::c_colorpicker::think()
{
	
}

static math_wraper::c_color bar_colors[7] = {
			math_wraper::c_color(255, 0, 0, 255),
			math_wraper::c_color(255, 255, 0, 255),
			math_wraper::c_color(0, 255, 0, 255),
			math_wraper::c_color(0, 255, 255, 255),
			math_wraper::c_color(0, 0, 255, 255),
			math_wraper::c_color(255, 0, 255, 255),
			math_wraper::c_color(255, 0, 0, 255)
};

void gui::c_colorpicker::think_new_layer()
{
	
}

void gui::c_colorpicker::handle_input(bool is_popup)
{
	// do input handler
	if (!is_popup) {
		if (g_ctx->block_input)
			return; // do not run if we block the input
	}

	// get active object id
	size_t active_object = g_modular->hash(this->title + g_ctx->parent_child);

	// get frame
	this->hovered = input_wraper::frame_from_region(math_wraper::c_vector_2d(this->pos.x, this->pos.y), math_wraper::c_vector_2d(14, 14));
	bool clicked = this->hovered && input_wraper::mouse_clicked(ImGuiMouseButton_Left);

	if (g_ctx->active_object == 0) // there are no elements that are active and if we clicked
	{
		// gehto
		g_ctx->is_colorpicker = false;

		if (clicked) // set the global active object var to this object
		{
			g_ctx->block_input = true;
			g_ctx->active_object = active_object;

			// debugging
			// printf("[c_slider_float::handle_input] sent input\n");
		}
	}
	else if (g_ctx->active_object == active_object)
	{
		// weird stuff was there
	}
}

void gui::c_colorpicker::set_inlined(bool inlined, int parent_space)
{
	this->inlined = inlined;
	this->parent_space = parent_space;
}

gui::c_keybind::c_keybind(std::string title, key_var_t* var)
{
	this->title = title;
	this->var = var;
}

void gui::c_keybind::think()
{
	

}

static std::vector<std::string> modes = { "Always", "Hold", "Toggle" };

void gui::c_keybind::think_new_layer()
{
	
}

void gui::c_keybind::handle_input(bool is_popup)
{
	// do input handler
	if (!is_popup) {
		if (g_ctx->block_input)
			return; // do not run if we block the input
	}

	// get active object id
	size_t active_object = g_modular->hash(this->title + g_ctx->parent_child);

	// get frame
	this->hovered = input_wraper::frame_from_region(math_wraper::c_vector_2d(this->pos.x, this->pos.y), math_wraper::c_vector_2d(14, 14));
	bool clicked = this->hovered && input_wraper::mouse_clicked(ImGuiMouseButton_Left);

	if (g_ctx->active_object == 0) // there are no elements that are active and if we clicked
	{
		if (clicked) // set the global active object var to this object
		{
			g_ctx->block_input = true;
			g_ctx->active_object = active_object;

			// debugging
			// printf("[c_slider_float::handle_input] sent input\n");
		}
	}
	else if (g_ctx->active_object == active_object)
	{
		math_wraper::c_vector_2d size = math_wraper::c_vector_2d(200, 120);
		math_wraper::c_vector_2d modes_size = math_wraper::c_vector_2d(size.x - 20, 30);
		math_wraper::c_vector_2d bind_pos = math_wraper::c_vector_2d(this->pos.x + 10, this->pos.y + 40 + modes_size.y + 10);
		math_wraper::c_vector_2d bind_size = math_wraper::c_vector_2d(size.x - 20, 30);

		bool skip_frame = false;
		if (input_wraper::frame_from_region(bind_pos, bind_size) && input_wraper::mouse_clicked(ImGuiMouseButton_Left)) {
			g_ctx->is_key_callback = true;
			skip_frame = false;

			printf("[c_keybind::handle_input] waiting for key input\n");
		}
		
		if (g_ctx->is_key_callback) {
			if (ImGui::IsKeyPressed(ImGuiKey_Escape, false) || ImGui::IsKeyPressed(ImGuiKey_Insert, false)) {
				(this->var)->key = 0;
				g_ctx->is_key_callback = false;
			}
			else {
				for (auto i = 0; i < 5; i++) {
					if (ImGui::GetIO().MouseClicked[i] && !skip_frame) {
						this->var->key = -1;
					}
				}

				// yeah this is bugged
				for (int i = 0; i < 255; i++) {
					if (ImGui::GetIO().MouseClicked[i]) {
						switch (i) {
						case 0:
							this->var->key = VK_LBUTTON;
							break;
						case 1:
							this->var->key = VK_RBUTTON;
							break;
						case 2:
							this->var->key = VK_MBUTTON;
							break;
						case 3:
							this->var->key = VK_XBUTTON1;
							break;
						case 4:
							this->var->key = VK_XBUTTON2;
							break;
						}
					}
					

					if (ImGui::IsKeyPressed(ImGuiKey(i), false)) {
						this->var->key = i;

						g_ctx->is_key_callback = false;
					}
				}
			}
		}
		
	}
}

void gui::c_keybind::set_inlined(bool inlined, int parent_space)
{
	this->inlined = inlined;
	this->parent_space = parent_space + this->key_name;
}

#pragma optimize("", on)

gui::c_textinput::c_textinput(std::string title, std::string* var)
{
	this->title = title;
	this->var = var;
}

float _blink2;

void gui::c_textinput::think()
{
	
}


std::string to_upper(std::string s) {
	std::transform(s.begin(), s.end(), s.begin(),
		[](unsigned char c) { return toupper(c); });
	return s;
}

void gui::c_textinput::handle_input(bool is_popup)
{
	// do input handler
	if (!is_popup) {
		if (g_ctx->block_input)
			return; // do not run if we block the input
	}

	// get active object id
	size_t active_object = g_modular->hash(this->title + g_ctx->parent_child);

	// get frame
	this->hovered = input_wraper::frame_from_region(math_wraper::c_vector_2d(this->pos.x, this->pos.y + framework::fonts->poppins_regular.measure(this->title).y + 5), math_wraper::c_vector_2d(g_ctx->parent_width, 26));
	bool clicked = this->hovered && input_wraper::mouse_clicked(ImGuiMouseButton_Left);

	if (g_ctx->active_object == 0) // there are no elements that are active and if we clicked
	{
		if (clicked) // set the global active object var to this object
		{
			g_ctx->active_object = active_object;

			// debugging
			// printf("[c_slider_float::handle_input] sent input\n");
		}
	}
	else if (g_ctx->active_object == active_object) {
		std::string str = *this->var;
		
		printf("here\n");	

		for (int i = 0; i < 255; i++) {
			if (ImGui::IsKeyPressed(ImGuiKey(i))) {
				// Ignore certain keys
				if (i == VK_ESCAPE || i == VK_RETURN || i == VK_INSERT || i == VK_DELETE) {
					g_ctx->active_object = 0;
					continue;
				}

				// Handle space key
				if (i == VK_SPACE) {
					str.append(" ");
					continue;
				}

				// Handle backspace key
				if (i == VK_BACK) {
					if (!str.empty()) {
						str = str.substr(0, str.length() - 1);
					}
					continue;
				}

				// Ignore Shift key itself
				if (i == VK_SHIFT || i == VK_LSHIFT || i == VK_RSHIFT) {
					continue;
				}

				// Handle other keys
				if (handler::key_names[i] != nullptr) {
					if (ImGui::IsKeyDown((ImGuiKey)VK_SHIFT) || ImGui::IsKeyDown((ImGuiKey)VK_LSHIFT) || ImGui::IsKeyDown((ImGuiKey)VK_RSHIFT)) {
						str.append(to_upper(handler::key_names[i])); // Convert to uppercase
					}
					else {
						str.append(handler::key_names[i]); // Use as is
					}
				}
			}
		}

		*var = str;
	}
}
