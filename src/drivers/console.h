#ifndef SBB_DRIVERS_CONSOLE_H
#define SBB_DRIVERS_CONSOLE_H

namespace sbb {

void ConsoleInit();
void ConsoleClose();

void ConsolePrintF(const char * format, ...);

}  // namespace sbb

#endif  // SBB_DRIVERS_CONSOLE_H
