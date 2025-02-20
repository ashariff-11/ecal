import unittest
import ecal.nanobind_core as ecal_transport

class TestECALTransportLayer(unittest.TestCase):

    def test_udp_network_configuration(self):
        config = ecal_transport.UDPNetworkConfiguration()
        self.assertEqual(config.group, "239.0.0.1")
        self.assertEqual(config.ttl, 3)

        config.group = "239.0.0.2"
        config.ttl = 5
        self.assertEqual(config.group, "239.0.0.2")
        self.assertEqual(config.ttl, 5)

    def test_udp_local_configuration(self):
        config = ecal_transport.UDPLocalConfiguration()
        self.assertEqual(config.group, "127.255.255.255")
        self.assertEqual(config.ttl, 1)

        config.group = "127.255.255.254"
        config.ttl = 2
        self.assertEqual(config.group, "127.255.255.254")
        self.assertEqual(config.ttl, 2)

    def test_udp_configuration(self):
        config = ecal_transport.UDPConfiguration()
        self.assertEqual(config.port, 14002)
        self.assertFalse(config.npcap_enabled)

        config.port = 15000
        config.npcap_enabled = True
        self.assertEqual(config.port, 15000)
        self.assertTrue(config.npcap_enabled)

    def test_tcp_configuration(self):
        config = ecal_transport.TCPConfiguration()
        self.assertEqual(config.number_executor_reader, 4)
        self.assertEqual(config.number_executor_writer, 4)
        self.assertEqual(config.max_reconnections, 5)

        config.number_executor_reader = 8
        config.number_executor_writer = 6
        config.max_reconnections = 10
        self.assertEqual(config.number_executor_reader, 8)
        self.assertEqual(config.number_executor_writer, 6)
        self.assertEqual(config.max_reconnections, 10)

    def test_transport_configuration(self):
        transport_config = ecal_transport.TransportConfiguration()

        self.assertIsInstance(transport_config.udp, ecal_transport.UDPConfiguration)
        self.assertIsInstance(transport_config.tcp, ecal_transport.TCPConfiguration)

        # Modify UDP Configuration
        transport_config.udp.port = 16000
        self.assertEqual(transport_config.udp.port, 16000)

        # Modify TCP Configuration
        transport_config.tcp.max_reconnections = 7
        self.assertEqual(transport_config.tcp.max_reconnections, 7)


if __name__ == '__main__':
    unittest.main()
