#ifndef EVENT_H
#define EVENT_H
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <server.hpp>
#define LEN_HEADER 4
#define MAX_LEN_BODY 512
using namespace std;

#define MAX_EVENT_PRIORRITY 10
#define NUM_EVENT_GENERATOR 100

class Packet
{
public:
	Packet()
		: body_length_(0)
	{}
	~Packet() = default;
	const char* getData() const { return data_; }
	char* data() { return data_; }
	std::size_t getLen() const { return LEN_HEADER + body_length_; }
	const char* getBody() const { return data_ + LEN_HEADER; }
	char* body() { return data_ + LEN_HEADER; }
	std::size_t getBodyLen() const { return body_length_; }
	void setBodyLen(std::size_t body_length);
	void encodeHeader();
	bool decodeHeader();
private:
	char data_[LEN_HEADER + MAX_LEN_BODY];
  	std::size_t body_length_;
};

class Event
{
	friend ostream& operator<<(ostream& fout, const Event& e);
public:
	Event() = default;
	~Event() = default;
	Event(int evt_no, int evt_pri, int genAddr);
	Event(int evt_no, int evt_pri, int genAddr, Session* pSession);
	Event(const Event& evt);
	void setEventNo(int evtNo) { event_no = evtNo; }
	void setEventGenAddr(int evtGenAddr) { event_gen_addr = evtGenAddr; }
	void setEventHandlerAddr(int evtHndlerAddr) { event_handler_adrr = evtHndlerAddr; }
	void setEventPriority(int evtPrior) { event_pri = evtPrior; }
	enum EventStatus { GENERATED, ENQUEUED, PROCESSED, UNDEFINED };
	
	void setEventStatus(EventStatus evtStatus) { eventStatus = evtStatus; }
	void setEventElapsedTime(double t_elapsed_ms) { t_elapsed_time_ms = t_elapsed_ms; }
	void setEventGenTime(timespec t_gen) { t_event_gen = t_gen; }
	void setEventProcTime(timespec t_proc) { t_event_proc = t_proc; }
	void setEventPacket(Packet evt_pkt) { event_pkt = evt_pkt; }
	int getEventPri() { return event_pri; }
	int getEventNo() { return event_no; }
	double getEventElapsedTime() { return t_elapsed_time_ms; }
	timespec getEventGenTime() { return t_event_gen; }
	timespec getEventProcTime() { return t_event_proc; }
	Packet& getEventPacket() { return event_pkt; }
	bool operator>(Event& e) { return event_pri > e.event_pri; }
	bool operator<(Event& e) { return event_pri < e.event_pri; }
	
private:
	int event_no;
	int event_gen_addr;
	int event_handler_adrr;
	int event_pri;
	timespec t_event_gen;
	timespec t_event_proc;
	Packet event_pkt;
	double t_elapsed_time_ms;
	std::shared_ptr<Session> pSession;
	EventStatus eventStatus;
};

#endif