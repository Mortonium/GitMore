#include "Settings.hpp"

Settings::Settings() {
	resetColors();
}
void Settings::resetColors() {
	init_pair(Colors::InvalidCLIToken, COLOR_RED, COLOR_BLACK);

}