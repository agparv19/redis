#include "common.h"


void die(const char* msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void msg(const char *msg) {
    fprintf(stderr, "%s\n", msg);
}

void print(const char *msg) {
    fprintf(stdout, "%s\n", msg);
}

std::string to_lower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c){ return std::tolower(c); });
    return result;
}


bool have_crlf(const char* buf, int len) {
    // returns true if buf has a CRLF 
    // within len bytes starting from buf
    int i = 0;
    while((buf[i] != '\r') && (i < len)) {
        i++;
    }
    if (i == len || i == len-1) {
        return false;
    } else if (buf[i+1] == '\n') {
        return true;
    } else {
        throw IncorrectProtocol("LF did not follow CR!");
    }
}

int recv_exactly(int fd, char* buf, size_t n_bytes) {
    while (n_bytes > 0) {
        ssize_t bytesRead = recv(fd, buf, n_bytes, 0);
        if (bytesRead <= 0) {
            perror("recv");
            return -1; //error
        }
        assert((size_t)bytesRead <= n_bytes);
        n_bytes -= (size_t)bytesRead;
        buf += (size_t)bytesRead;
    }
    return 0; // success
}


int write_exactly(int fd, const char* buf, size_t n_bytes) {
    while (n_bytes > 0) {
        ssize_t bytesSent = send(fd, buf, n_bytes, 0);
        if (bytesSent <= 0) {
            perror("send");
            return -1; // error
        }
        assert((size_t)bytesSent <= n_bytes);
        n_bytes -= (size_t)bytesSent;
        buf += (size_t)bytesSent;
    }
    return 0; // success
}

int recv_one_packet(int fd, char* buf) {
    // buf must have atleast 4 + MAX_PACKET_SIZE + 1 reserved
    // one packet is len + data
    // len is a 4 byte integer in little endian
    // read 4 bytes header i.e. len of data
    if (recv_exactly(fd, buf, 4) == -1) {
        return -1;
    }
    uint32_t len = 0;
    memcpy(&len, buf, 4);
    if (len > MAX_PACKET_SIZE) {
        msg("packet too long");
        return -1; // failure
    }

    if (recv_exactly(fd, &buf[4], len) == -1){
        msg("data read error");
        return -1; // failure
    }
    buf[4+len] = '\0';

    // probably not the best way to print but mehh
    std::stringstream ss;
    ss << "received packet of length: " << len;
    print(ss.str().c_str());

    return 0; // success
}

int send_one_packet(int fd, const char* buf) {
    // buf constains the data to be sent
    // buf *must* be null terminated
    uint32_t len = strlen(buf);
    if (len > MAX_PACKET_SIZE) {
        msg("packet too long");
        return -1; // failure
    }
    char wbuf[4 + len];
    memcpy(wbuf, &len, 4);
    memcpy(&wbuf[4], buf, len);
    if (write_exactly(fd, wbuf, 4+len) == -1) {
        return -1; // failure
    } 

    // probably not the best way to print but mehh
    std::stringstream ss;
    ss << "sent packet of length: " << len;
    print(ss.str().c_str());

    return 0;
}
