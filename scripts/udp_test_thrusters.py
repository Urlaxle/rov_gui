import socket
import time

def send_udp_message(message, ip='127.0.0.1', port=12345):
    """
    Sends a UDP message to the specified IP and port.

    :param message: The string message to send.
    :param ip: The target IP address (default is localhost).
    :param port: The target port (default is 12345).
    """
    try:
        # Create a UDP socket
        udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

        # Send the message
        udp_socket.sendto(message.encode('utf-8'), (ip, port))
        print(f"Message sent to {ip}:{port}: {message}")

        # Close the socket
        udp_socket.close()
    except Exception as e:
        print(f"Error: {e}")

# Example usage
if __name__ == "__main__":
    # Define your message here
    test_message = "$THR,50,-50,50,-50,50,-50,50"
    test_port = 8571  # Change to match your terminal's listening port
    amount = 100
    for i in range(amount):
        send_udp_message(test_message, port=test_port)
        time.sleep(0.1)
