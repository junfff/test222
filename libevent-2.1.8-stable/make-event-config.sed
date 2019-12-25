# Sed script to postprocess config.h into event-config.h.

1i\
/* event2/event-config.h\
 *\
 * This file was generated by autoconf when libevent was built, and post-\
 * processed by Libevent so that its macros would have a uniform prefix.\
 *\
 * DO NOT EDIT THIS FILE.\
 *\
 * Do not rely on macros in this file existing in later versions.\
 */\
\
#ifndef EVENT2_EVENT_CONFIG_H_INCLUDED_\
#define EVENT2_EVENT_CONFIG_H_INCLUDED_\

$a\
\
#endif /* event2/event-config.h */

s/#\( *\)define /#\1define EVENT__/
s/#\( *\)undef /#\1undef EVENT__/
s/#\( *\)if\(n*\)def /#\1if\2def EVENT__/
