/**************************************************************************
 * qDecoder - Web Application Interface for C/C++   http://www.qDecoder.org
 *
 * Copyright (C) 2007 Seung-young Kim.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "qDecoder.h"

int main(void) {
	/* Parse (GET/COOKIE/POST) queries. */
	Q_ENTRY *req = qCgiRequestParse(NULL);

	const char *mode = qEntryGetStr(req, "mode");
	const char *name = qEntryGetStr(req, "cname");
	const char *value = qEntryGetStr(req, "cvalue");

	if (mode == NULL) { /* View Cookie */
		qCgiResponseSetContentType(req, "text/plain");
		printf("Total %d entries\n", qEntryGetNum(req));
		qEntryPrint(req, stdout, true);
	} else if (!strcmp(mode, "set")) { /* Set Cookie */
		if (name == NULL || value == NULL) qCgiResponseError(req, "Query not found");
		if (strlen(name) == 0) qCgiResponseError(req, "Empty cookie name can not be stored.");

		qCgiResponseSetCookie(req, name, value, 0, NULL, NULL, false);
		qCgiResponseSetContentType(req, "text/html");
		printf("Cookie('%s'='%s') entry is stored.<br>Click <a href='cookie.cgi'>here</a> to view your cookies\n", name, value);
	} else if (!strcmp(mode, "remove")) { /* Remove Cookie */
		if (name == NULL) qCgiResponseError(req, "Query not found");
		if (!strcmp(name, "")) qCgiResponseError(req, "Empty cookie name can not be removed.");

		qCgiResponseRemoveCookie(req, name, NULL, NULL, false);
		qCgiResponseSetContentType(req, "text/html");
		printf("Cookie('%s') entry is removed.<br>Click <a href='cookie.cgi'>here</a> to view your cookies\n", name);
	} else {
		qCgiResponseError(req, "Unknown mode.");
	}

	qEntryFree(req);
	return 0;
}
