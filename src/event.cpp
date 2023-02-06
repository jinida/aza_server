#include "event.hpp"

void Packet::setBodyLen(std::size_t body_length)
{ 
	body_length_ = body_length;
	if (body_length_ > MAX_LEN_BODY)
	{
		body_length_ = MAX_LEN_BODY;
	}
}

void Packet::encodeHeader()
{
	char header[LEN_HEADER + 1] = "";
	std::sprintf(header, "%4d", static_cast<int>(body_length_));
	std::memcpy(data_, header, LEN_HEADER);
}

bool Packet::decodeHeader()
{
	char header[LEN_HEADER + 1] = "";
	std::strncat(header, data_, LEN_HEADER);
	body_length_ = std::atoi(header);
	if (body_length_ > MAX_LEN_BODY)
	{
	body_length_ = 0;
	return false;
	}
	return true;
}

Event::Event(int evt_no, int evt_pri, int genAddr)
{
	this->event_no = evt_no;
	this->event_pri = evt_pri;
	this->event_gen_addr = genAddr;
	this->event_handler_adrr = -1;
	this->eventStatus = GENERATED;
}

Event::Event(int evt_no, int evt_pri, int genAddr, std::shared_ptr<Session> pSession)
{
	this->event_no = evt_no;
	this->event_pri = evt_pri;
	this->event_gen_addr = genAddr;
	this->event_handler_adrr = -1;
	this->eventStatus = GENERATED;
	this->pSession_ = pSession;
}

Event::Event(const Event& evt)
{
	this->event_no = evt.event_no;
	this->event_pri = evt.event_pri;
	this->event_gen_addr = evt.event_gen_addr;
	this->event_handler_adrr = evt.event_handler_adrr;
	this->eventStatus = evt.eventStatus;
	this->pSession_ = evt.pSession_;
}

Event* genRandEvent(int evt_no)
{
	Event* pEv;
	int evt_prio;
	int evt_generator_id;
	evt_prio = rand() % MAX_EVENT_PRIORRITY;
	evt_generator_id = rand() & NUM_EVENT_GENERATOR;
	pEv = new Event(evt_no, evt_prio, evt_generator_id);
	return pEv;
}

ostream& operator<<(ostream& fout, const Event& evt)
{
	fout << "Ev(no:" << setw(3) << evt.event_no;
	fout << ", pri:" << setw(3) << evt.event_pri << ") ";
    //fout << ", content: " << setw(10) << evt.event_content << "\n";

	return fout;
}