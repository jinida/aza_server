
// #ifndef PACKET_HPP
// #define PACKET_HPP

// #include <cstdio>
// #include <cstdlib>
// #include <cstring>
// #define LEN_HEADER 4
// #define MAX_LEN_BODY 512

// class Packet
// {
// public:
//   Packet()
//     : body_length_(0)
//   {
//   }

//   const char* data() const
//   {
//     return data_;
//   }

//   char* data()
//   {
//     return data_;
//   }

//   std::size_t length() const
//   {
//     return LEN_HEADER + body_length_;
//   }

//   const char* body() const
//   {
//     return data_ + LEN_HEADER;
//   }

//   char* body()
//   {
//     return data_ + LEN_HEADER;
//   }

//   std::size_t body_length() const
//   {
//     return body_length_;
//   }

//   void body_length(std::size_t new_length)
//   {
//     body_length_ = new_length;
//     if (body_length_ > MAX_LEN_BODY)
//       body_length_ = MAX_LEN_BODY;
//   }

//   bool decode_header()
//   {
//     char header[LEN_HEADER + 1] = "";
//     std::strncat(header, data_, LEN_HEADER);
//     body_length_ = std::atoi(header);
//     if (body_length_ > MAX_LEN_BODY)
//     {
//       body_length_ = 0;
//       return false;
//     }
//     return true;
//   }

//   void encode_header()
//   {
//     char header[LEN_HEADER + 1] = "";
//     std::sprintf(header, "%4d", static_cast<int>(body_length_));
//     std::memcpy(data_, header, LEN_HEADER);
//   }

// private:
//   char data_[LEN_HEADER + MAX_LEN_BODY];
//   std::size_t body_length_;
// };

// #endif