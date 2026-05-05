#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <array>
#include <tuple>

namespace serdes {

static constexpr char kPacketStart[] = "##";

static constexpr char kStartChar = '#';

static constexpr char kDigitMin = '0';
static constexpr char kDigitMax = '9';

static constexpr char kUpperAlphaMin = 'A';
static constexpr char kUpperAlphaMax = 'Z';

static constexpr char kPrintableAsciiMin = 0x20;
static constexpr char kPrintableAsciiMax = 0x7E;

template <std::size_t kMaxPayloadLen>
struct Packet {
    uint8_t device_id;
    uint8_t packet_type;

    std::array<char, kMaxPayloadLen> payload;
    std::size_t payload_len;
};

template <std::size_t kMaxPayloadLen>
class Serializer {
public:
    static bool Serialize(
        const Packet<kMaxPayloadLen>& src,
        uint8_t* dst,
        std::size_t max_len_dst
    );
    
    static uint16_t GetCrc16(
        const char* src,
        std::size_t len
    );
};

template <std::size_t kMaxPayloadLen>
class Deserializer {
public:
    enum class ErrorCode : uint8_t {
        InvalidStart,
        InvalidDeviceId,
        InvalidPacketType,
        InvalidLength,
        InvalidChecksum,
        PacketTooLarge,
        InvalidCharacter
    };

private: 
    using PacketHandler = 
        void(*)(const Packet<kMaxPayloadLen>&, void*);

    using ErrorHandler = 
        void(*)(const Packet<kMaxPayloadLen>&, ErrorCode);

    enum class State {
        WaitStart1,
        WaitStart2,

        ReadDeviceId,
        ReadPacketType,
        ReadLength,
        ReadPayload,
        ReadChecksum,
    };

public: 
    static bool Deserialize(
        const uint8_t* src,
        std::size_t frame_len,
        Packet<kMaxPayloadLen>& dst
    );

    void ProcessByte(uint8_t b);
    void Reset();

private:
    State deserializer_state_ { State::WaitStart };
    Packet<kMaxPayloadLen> current_packet_;
};

} // serdes

#endif