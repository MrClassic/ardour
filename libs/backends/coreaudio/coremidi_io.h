/*
 * Copyright (C) 2015 Robin Gareus <robin@gareus.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <CoreServices/CoreServices.h>
#include <CoreAudio/CoreAudio.h>
#include <AudioUnit/AudioUnit.h>

#include <AudioUnit/AudioUnit.h>
#include <AudioToolbox/AudioToolbox.h>

#include <map>
#include <vector>
#include <string>

#include <boost/shared_ptr.hpp>
#include "pbd/ringbuffer.h"

typedef struct _CoreMIDIPacket { 
	MIDITimeStamp timeStamp; 
	UInt16 length; 
	Byte data[256]; 
#if 0 // unused
	_CoreMIDIPacket (MIDITimeStamp t, Byte *d, UInt16 l)
		: timeStamp(t)
		, length (l)
	{
		if (l > 256) {
			length = 256;
		}
		if (length > 0) {
			memcpy(data, d, length);
		}
	}
#endif
	_CoreMIDIPacket (const MIDIPacket *other) 
		: timeStamp(other->timeStamp)
		, length (other->length)
	{
		if (length > 0) {
			memcpy(data, other->data, length);
		}
	}
} CoreMIDIPacket;

typedef std::vector<boost::shared_ptr<CoreMIDIPacket> > CoreMIDIQueue;

class CoreMidiIo {
public:
	CoreMidiIo (void);
	~CoreMidiIo (void);

	// TODO explicit start/stop, add/remove devices as needed.
	void discover ();
	void start_cycle ();

	int send_event (uint32_t, double, const uint8_t *, const size_t);
	size_t recv_event (uint32_t, double, uint64_t &, uint8_t *, size_t &);

	uint32_t n_midi_inputs (void) const { return _n_midi_in; }
	uint32_t n_midi_outputs (void) const { return _n_midi_out; }

	void notify_proc (const MIDINotification *message);

	void set_port_changed_callback (void (changed_callback (void*)), void *arg) {
		_changed_callback = changed_callback;
		_changed_arg = arg;
	}

private:
	void cleanup ();

	MIDIClientRef     _midi_client;
	MIDIEndpointRef * _input_endpoints;
	MIDIEndpointRef * _output_endpoints;
	MIDIPortRef     * _input_ports;
	MIDIPortRef     * _output_ports;
	CoreMIDIQueue   * _input_queue;

	RingBuffer<uint8_t> ** _rb;

	uint32_t          _n_midi_in;
	uint32_t          _n_midi_out;

	MIDITimeStamp     _time_at_cycle_start;
	bool              _active;

	void (* _changed_callback) (void*);
	void  * _changed_arg;
};