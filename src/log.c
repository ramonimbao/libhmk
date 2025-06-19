/*
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include "log.h"

#if defined(LOG_ENABLED)
#include <stdarg.h>
#include <stdio.h>

char log_buffer[LOG_BUFFER_SIZE];
uint32_t log_buffer_size;

void log_init(void) {}

void log_printf(const char *fmt, ...) {
<<<<<<< HEAD
=======
  if (log_buffer_size >= LOG_BUFFER_SIZE - 1)
    // Buffer is full, cannot log more
    return;

>>>>>>> 1390ccf91b3075c126efce8016e409c079348e44
  va_list args;

  va_start(args, fmt);
  int len = vsnprintf(NULL, 0, fmt, args);
  va_end(args);

<<<<<<< HEAD
  if (len <= 0 || log_buffer_size + len >= LOG_BUFFER_SIZE)
    // Buffer overflow, or invalid length
=======
  if (len <= 0)
    // Invalid length
>>>>>>> 1390ccf91b3075c126efce8016e409c079348e44
    return;

  va_start(args, fmt);
  vsnprintf(log_buffer + log_buffer_size, LOG_BUFFER_SIZE - log_buffer_size,
            fmt, args);
  va_end(args);

  log_buffer_size += len;
}

void log_clear(void) {
  log_buffer[0] = '\0';
  log_buffer_size = 0;
}
#endif