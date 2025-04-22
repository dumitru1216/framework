#pragma once
#pragma warning (disable: 4996)
#include <codecvt>

// just an ass defne
#define make_object(a, b) inline std::shared_ptr<b> a = std::make_shared<b>()
#define element_identation 30
#define element_spacing 10
#define max_childs 100

namespace gui {
	namespace handler {
		inline const char* const key_names[] = {
	"none",
	"m1",
	"m2",
	"something",
	"m3",
	"m4",
	"m5",
	"unk",
	"back",
	"tab",
	"unk",
	"unk",
	"clear",
	"enter",
	"unk",
	"unk",
	"shift",
	"control",
	"menu",
	"pause",
	"capital",
	"kana",
	"unk",
	"junja",
	"final",
	"kanja",
	"unk",
	"escape",
	"convert",
	"nonconvert",
	"accept",
	"modechange",
	"space",
	"prior",
	"next",
	"end",
	"home",
	"left",
	"up",
	"right",
	"down",
	"select",
	"print",
	"exec",
	"snap",
	"insert",
	"delete",
	"help",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"unk",
	"unk",
	"unk",
	"unk",
	"unk",
	"unk",
	"unk",
	"a",
	"b",
	"c",
	"d",
	"e",
	"f",
	"g",
	"h",
	"i",
	"j",
	"k",
	"l",
	"m",
	"n",
	"o",
	"p",
	"q",
	"r",
	"s",
	"t",
	"u",
	"v",
	"w",
	"x",
	"y",
	"z",
	"lwin",
	"rwin",
	"apps",
	"unk",
	"sleep",
	"num0",
	"num1",
	"num2",
	"num3",
	"num4",
	"num5",
	"num6",
	"num7",
	"num8",
	"num9",
	"multiply",
	"add",
	"separator",
	"subtract",
	"dec",
	"divide",
	"f1",
	"f2",
	"f3",
	"f4",
	"f5",
	"f6",
	"f7",
	"f8",
	"f9",
	"f10",
	"f11",
	"f12",
	"f13",
	"f14",
	"f15",
	"f16",
	"f17",
	"f18",
	"f19",
	"f20",
	"f21",
	"f22",
	"f23",
	"f24",
	"unk",
	"unk",
	"unk",
	"unk",
	"unk",
	"unk",
	"unk",
	"unk",
	"numlock",
	"scroll",
	"VK_OEM_NEC_EQUAL",
	"VK_OEM_FJ_MASSHOU",
	"VK_OEM_FJ_TOUROKU",
	"VK_OEM_FJ_LOYA",
	"VK_OEM_FJ_ROYA",
	"unk",
	"unk",
	"unk",
	"unk",
	"unk",
	"unk",
	"unk",
	"unk",
	"unk",
	"lshift",
	"rshit",
	"lcontrol",
	"rcontrol",
	"lwin",
	"rwin"
		};
	}

	class c_proffiler {
	public:
		void add_to_profiler(std::string profiler) {
			logs.push_back(profiler);
		}

		void draw_proffiler() {
			if (logs.empty())
				return;

			for (int i = 0; i < logs.size(); i++) {
				framework::fonts->menu_default.draw(10, 10 + (25 * i), logs[i], math_wraper::c_color());
			}

			logs.clear();
		}

	private:
		std::vector<std::string> logs{};
	};
	make_object(g_profiler, c_proffiler);

	// theme
	class c_theme {
	public:
		math_wraper::c_color blended_backround = math_wraper::c_color(6, 6, 6);
		math_wraper::c_color backround = math_wraper::c_color(16, 16, 16);
		math_wraper::c_color tab_second = math_wraper::c_color(20, 20, 20);
		math_wraper::c_color child_backround = math_wraper::c_color(18, 18, 18);
		math_wraper::c_color outliner = math_wraper::c_color(35, 35, 35);
		math_wraper::c_color arrow_color = math_wraper::c_color();

		math_wraper::c_color accent = math_wraper::c_color(255, 0, 0);

		// elements
		math_wraper::c_color element_backround = math_wraper::c_color(12, 12, 12);
		math_wraper::c_color scroll_thumb = math_wraper::c_color(10, 10, 10);
		math_wraper::c_color scroll_track = math_wraper::c_color(28, 28, 28);
	};
	make_object(g_theme, c_theme);

	// context
	class c_context {
	public:
		bool dragging{}, scrolling{}, block_input{ false }, is_colorpicker{ false }, is_key_callback{ false }, is_frame_open{ false }, is_keybind{ false }, is_popup{ false };
		int parent_width{}, active_popup{}, active_tab{ 0 }, active_subtab{ 0 };
		size_t active_object{};

		std::string parent_child{}, cur_tab{}, cur_subtab{};
		std::vector<std::string> tabs{};
		std::vector<std::string> sub_tabs{};

		bool initialized_stack_members{false};

		math_wraper::c_color clipboard{};
		float hsv_clipboard{};

		// frame data
		float frame_alpha{};
	};
	make_object(g_ctx, c_context);

	class c_modulars {
	public:
		__forceinline std::string wstring_to_string(const wchar_t* wstr) {
			std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
			return converter.to_bytes(wstr);
		}

		template <typename T>
		__forceinline std::string precision(const T a_value, const int n = 3) {
			std::ostringstream out;
			out.precision(n);
			out << std::fixed << a_value;
			return out.str();
		}

		__forceinline size_t hash(const std::string& str)
		{
			return std::hash< std::string >()(str);
		}

		__forceinline float modulate_float(float input, float input_min, float input_max, float output_min, float output_max)
		{
			return (input - input_min) / (input_max - input_min) * (output_max - output_min) + output_min;
		}

		float create_animation(std::string indentifier, bool target, bool int_animation = false, int min = 0, int max = 0) {
			framework::anim_context_t anim = framework::g_anim_base.build(indentifier + g_ctx->parent_child);

			if (int_animation) {
				anim.animate_int(anim.m_value + 3.f * framework::g_anim_base.delta_time(0.3) * (target ? 255.f : -255.f), true, min, max);
			}
			else {
				anim.animate(anim.m_value + 3.f * framework::g_anim_base.delta_time(0.3) * (target ? 1.f : -1.f));
			}

			return anim.m_value;
		}

		std::string get_key_name(const int VirtualKey) {
			auto Code = MapVirtualKeyA(VirtualKey, MAPVK_VK_TO_VSC);

			int Result;
			char Buffer[128];

			switch (VirtualKey) {
			case VK_LEFT: case VK_UP: case VK_RIGHT: case VK_DOWN:
			case VK_RCONTROL: case VK_RMENU:
			case VK_LWIN: case VK_RWIN: case VK_APPS:
			case VK_PRIOR: case VK_NEXT:
			case VK_END: case VK_HOME:
			case VK_INSERT: case VK_DELETE:
			case VK_DIVIDE:
			case VK_NUMLOCK:
				Code |= KF_EXTENDED;
			default:
				Result = GetKeyNameTextA(Code << 16, Buffer, 128);
			}

			if (Result == 0 || VirtualKey == VK_CAPITAL) {
				switch (VirtualKey) {
				case VK_XBUTTON1:
					return ("M4");
				case VK_XBUTTON2:
					return ("M5");
				case VK_LBUTTON:
					return ("M1");
				case VK_MBUTTON:
					return ("M3");
				case VK_RBUTTON:
					return ("M2");
				case VK_CAPITAL:
					return ("CAPS");
				default:
					return ("Bind a key!");
				}
			}

			auto transformer = std::string(Buffer);
			std::transform(transformer.begin(), transformer.end(), transformer.begin(), ::toupper);

			return transformer;
		}
	};
	make_object(g_modular, c_modulars);

	// tabs system, TOTTALY DOGSHIT
	class c_tab {
	public:
		bool add_tab(std::string tab_string);
		bool add_subtab(std::string subtab_string);
	};
	// make_object(g_tab, c_tab);

	class c_checkbox {
	public:
		// constructor and deconstructor
		c_checkbox(std::string label, bool* value);
		// ~c_checkbox(); automatically managed
	public:
		void think();
		void handle_input(bool is_popup = false);
	private:
		// vars in which we store the input from constructor
		std::string label{};
		bool* value{};
	public:
		// element frame
		math_wraper::c_vector_2d pos{};
	};

	class c_slider_float {
	public:
		// constructor and deconstructor
		c_slider_float(std::string title, float* val, float min, float max, std::wstring suf = L"");
		// ~c_slider_float(); automatically managed
	public:
		void think();
		void handle_input(bool is_popup = false);
	private:
		// vars in which we store the input from constructor
		std::string title{};
		std::wstring suf{};

		float* value{};
		float min{}, max{};
		bool hovered{};
	public:
		// element frame
		math_wraper::c_vector_2d pos{};
	};

	class c_slider_int {
	public:
		// constructor and deconstructor
		c_slider_int(std::string title, int* val, int min, int max, std::wstring suf = L"");
		// ~c_slider_int(); automatically managed
	public:
		void think();
		void handle_input(bool is_popup = false);
	private:
		// vars in which we store the input from constructor
		std::string title{};
		std::wstring suf{};

		int* value{};
		int min{}, max{};
		float* animated_value{};
		bool hovered{};
	public:
		// element frame
		math_wraper::c_vector_2d pos{};
	};

	class c_combo {
	public:
		// constructor
		//c_combo(std::string title, int* val, const std::vector<std::string>& items); // constructor as items for var
		c_combo(std::string title, int* val, std::vector<std::string> items); // constructor as items in constructor
	public:
		void think();
		void think_new_layer();

		void handle_input(bool is_popup = false);
	private:
		// vars in which we store the input from constructor
		std::string title{};
		std::vector<std::string> items{};

		int* val{};
		bool hovered{};
	public:
		bool opened{ false };
		float height{};

		// element frame
		math_wraper::c_vector_2d pos{};
	};

	// context for multicombo
	class c_combo_context {
	public:
		c_combo_context(std::string title, bool* var) {
			this->title = title;
			this->value = var;
		}
	public:
		bool* value{};
		std::string title{};
	};

	class c_multi_combo {
	public:
		// construcotr
		c_multi_combo(std::string title); // define just the title, we dont need to define anything else
	public:
		// access through the created shared_ptr<c_multi_combo>
		void bind(std::string title, bool* var);

		// main handling
		void think();
		void think_new_layer();

		void handle_input(bool is_popup = false);
	private:
		// bind function will push items added
		std::vector<c_combo_context> items{};
		std::string title{};

		bool hovered{};
	public:
		// element frame
		math_wraper::c_vector_2d pos{};

		bool opened{ false };
		float height{};
	};

	class c_button {
	public:
		// constructor
		c_button(std::string title, std::function<void()> fn);
	public:
		void think();
		void handle_input(bool is_popup = false);
	private:
		std::string title{};
		std::function<void()> fn{};

		bool hovered{};
	public:
		// element frame
		math_wraper::c_vector_2d pos{};
	};

	class c_listbox {
	public:
		c_listbox(std::string title, int* val, std::vector<std::string> items);
	public:
		void think();
		void handle_input();

		void set_height(int height);
	private:
		// vars in which we store the input from constructor
		std::string title{};
		std::vector<std::string> items{};

		int height{150};
		int* val{};
		bool hovered{};
	public:
		// element frame
		math_wraper::c_vector_2d pos{};
	};

	struct color_var_t {
		math_wraper::c_color color{};
		float hue{};
	};

	struct RGB { double r, g, b; };
	struct HSV { double h, s, v; };

	class c_colorpicker {
	public:
		c_colorpicker(std::string title, color_var_t* color);
	private:
		__forceinline HSV rgb_to_hsv(const RGB& In) {
			HSV m_Result;
			double Min, Max, Delta;

			Min = In.r < In.g ? In.r : In.g;
			Min = Min < In.b ? Min : In.b;

			Max = In.r > In.g ? In.r : In.g;
			Max = Max > In.b ? Max : In.b;

			m_Result.v = Max;
			Delta = Max - Min;

			if (Delta < 0.0001) {
				m_Result.s = 0;
				m_Result.h = 0;

				return m_Result;
			}

			if (Max > 0) {
				m_Result.s = (Delta / Max);
			}
			else {
				m_Result.s = 0;
				m_Result.h = NAN;

				return m_Result;
			}

			if (In.r >= Max) {
				m_Result.h = (In.g - In.b) / Delta;
			}
			else {
				if (In.g >= Max) {
					m_Result.h = 2 + (In.b - In.r) / Delta;
				}
				else {
					m_Result.h = 4 + (In.r - In.g) / Delta;
				}
			}

			m_Result.h *= 60;

			if (m_Result.h < 0)
				m_Result.h += 360;

			return m_Result;
		}
		__forceinline RGB hsv_to_rgb(const HSV& In) {
			RGB m_Result;

			double HH, P, Q, T, FF;
			long i;

			if (In.s <= 0) {
				m_Result.r = In.v;
				m_Result.g = In.v;
				m_Result.b = In.v;

				return m_Result;
			}

			HH = (In.h >= 360 ? 0 : In.h) / 60;
			i = (long)HH;

			FF = HH - i;

			P = In.v * (1 - In.s);
			Q = In.v * (1 - (In.s * FF));
			T = In.v * (1 - (In.s * (1 - FF)));

			switch (i) {
			case 0:
				m_Result.r = In.v;
				m_Result.g = T;
				m_Result.b = P;

				break;

			case 1:
				m_Result.r = Q;
				m_Result.g = In.v;
				m_Result.b = P;

				break;

			case 2:
				m_Result.r = P;
				m_Result.g = In.v;
				m_Result.b = T;

				break;

			case 3:
				m_Result.r = P;
				m_Result.g = Q;
				m_Result.b = In.v;

				break;

			case 4:
				m_Result.r = T;
				m_Result.g = P;
				m_Result.b = In.v;

				break;

			case 5:
			default:
				m_Result.r = In.v;
				m_Result.g = P;
				m_Result.b = Q;

				break;

			}

			return m_Result;
		}
	public:
		void think();
		void think_new_layer();

		void handle_input(bool is_popup = false);

		void set_inlined(bool inlined = false, int parent_space = 0);
	private:
		// vars in which we store the input from constructor
		std::string title{};
		color_var_t* var{};

		bool hovered{}, hovered_panel{}, hover_copy{}, hover_paste{};
		bool is_modifying_hsv{}, is_modifying_alpha{}, is_modifying_hue{};
		bool in_area_hsv{}, in_area_alpha{}, in_area_hue{};

		//math_wraper::c_vector_2d mouse_hsv{};
	public:
		bool inlined{};
		int parent_space{};

		// element frame
		math_wraper::c_vector_2d pos{}, cursor_pos{}, prev_cursor_pos{};
	};

	enum key_mode_t : int {
		// this is a bit ghetto but we can use this to define the keybind mode
		always = 0,
		hold = 1,
		toggle = 2,
	};

	// TOTAL DOSHIT
	struct key_var_t {
		int key{}, mode{};

		// yeah i guess we can make this our main input system for keybind
		bool active() {
			if (this->key <= 0 || this->key > 255) {
				return false; // invalid key
			}

			if (this->mode == key_mode_t::always) {
				// this is always on
				return true;
			}
			else if (this->mode == key_mode_t::toggle) {
				return GetKeyState(key); // this should return true or false
			}
			else if (this->mode == key_mode_t::hold) {
				return GetAsyncKeyState(key); // this should return true or false
			}
			else {
				return false;
			}
		}
	};

	// create elements in cpp file
	class c_keybind {
	public:
		// consttructor, this might be wrong, we should also add a keybind title (do not forget this)
		c_keybind(std::string title, key_var_t* var);
	public:
		void think();
		void think_new_layer();

		void handle_input(bool is_popup = false); // handle input
		void set_inlined(bool inlined = false, int parent_space = 0);
	private:
		std::string title{};
		key_var_t* var{};

		bool hovered{}, hovered_panel{};
	public:
		bool inlined{};
		int parent_space{}, key_name{};

		// area
		math_wraper::c_vector_2d pos{};
	};

	class c_textinput {
	public:
		c_textinput(std::string title, std::string* var);
	public:
		void think();
		void handle_input(bool is_popup = false);
	private:
		std::string title{};
		std::string* var{};

		bool hovered{};
	public:
		// area
		math_wraper::c_vector_2d pos{};
	};

	// child / page object
	enum page_elements_t : int {
		checkbox = 16,
		slider = 34,
		dropdown = 47,
		button = 26,
	};

	class c_popup {
	public:
		// constructor, the same as c_page but without position as it will be automatically initialized by parent pos -> element / page
		c_popup(std::string title, math_wraper::c_vector_2d size, int id);
	public:
		void post_initialization();
		void think();

		// this might be renamed
		void handle_input();
		void assign_elements(std::function<void()> elements_backend);

		void bind(const std::shared_ptr<c_checkbox>& element);
		void bind(const std::shared_ptr<c_slider_float>& element);
		void bind(const std::shared_ptr<c_slider_int>& element);
		void bind(const std::shared_ptr<c_combo>& element);
		void bind(const std::shared_ptr<c_multi_combo>& element);
		void bind(const std::shared_ptr<c_button>& element);
		void bind(const std::shared_ptr<c_colorpicker>& element);

		void prioritize_layer(const std::shared_ptr<c_combo>& element);
		void prioritize_layer(const std::shared_ptr<c_multi_combo>& element);
		void prioritize_layer(const std::shared_ptr<c_colorpicker>& element);

		void clear_instance();

		int get_parent_elemnt(page_elements_t element);
		math_wraper::c_vector_2d get_parent_pos();

		void scrolling();
	public: // scrolling
		// this method is a bit gheto
		
	private:
		std::string title{};
		math_wraper::c_vector_2d size{};

		int id{};
		bool hovered{}, hovered_page{};

		std::function<void()> elements_backend{};

		// this is memory unsafe but whoever cares, if its gonna be out of bounds just crash :|
		struct element_layout_t {
			float x{}; // we dont need to overkill this shit
			float y[max_childs]{};
		};
		element_layout_t layout{};
	public: // we will initialize this by parent
		// element frame
		math_wraper::c_vector_2d pos{};
	};

	class c_page {
	public:
		// constructor and deconstructor
		c_page(std::string title, math_wraper::c_vector_2d position, math_wraper::c_vector_2d size, int id);
		// ~c_page(); automatically managed
	public:
		void think();
		void post_initialization();
		void clear_instance();
		void scrolling();
		void set_parent_position(math_wraper::c_vector_2d pos);
	public:
		int get_parent_elemnt(page_elements_t element);
		math_wraper::c_vector_2d get_parent_pos();

		void bind(const std::shared_ptr<c_checkbox>& element);
		void bind(const std::shared_ptr<c_slider_float>& element);
		void bind(const std::shared_ptr<c_slider_int>& element);
		void bind(const std::shared_ptr<c_combo>& element);
		void bind(const std::shared_ptr<c_multi_combo>& element);
		void bind(const std::shared_ptr<c_button>& element);
		void bind(const std::shared_ptr<c_listbox>& element);
		void bind(const std::shared_ptr<c_popup>& element);
		void bind(const std::shared_ptr<c_colorpicker>& element);
		void bind(const std::shared_ptr<c_keybind>& element);
		void bind(const std::shared_ptr<c_textinput>& element);
	private:
		math_wraper::c_vector_2d pos{}, size{};
		int id{};

		// this is memory unsafe but whoever cares, if its gonna be out of bounds just crash :|
		struct element_layout_t {
			float x{}; // we dont need to overkill this shit
			float y[max_childs]{};
		};
		element_layout_t layout{};
		std::string title{};
		bool hovered{};
	};

	// main window
	class c_window {
	public:
		// constructor
		c_window(std::string title, math_wraper::c_vector_2d* position, const math_wraper::c_vector_2d& size);
		
		// deconstructor
		// ~c_window(); automaticaly managed
	public:
		void think();
		void handle_input();

		void create_page(const std::shared_ptr<c_page>& page);
		bool is_opened();
	private:
		std::string title{};
		math_wraper::c_vector_2d* pos{};
		math_wraper::c_vector_2d size{};
	public:
		// tab pointer
		std::shared_ptr<c_tab> tab_pointer;
	};
	// make_object(g_window, c_window);

	// gui class
	class c_gui {
	public:
		void initialize();
	};
	make_object(g_frame, c_gui);
}