const dgram = require('dgram')
const net = require('net')
const os = require('os')

const BEACON_PORT = 7777
const COMMAND_PORT = 7778
const MULTICAST_ADDRESS = '224.0.0.42'

const beaconSocket = dgram.createSocket('udp4')
const socketCache = {}

beaconSocket.on('message', (buffer, udpinfo) => {
  if (String(buffer) === '42003d000f47343438323536') {
    sendCommand(udpinfo.address)
  } else {
    console.log('Received:', buffer)
    console.log('Info: %j', udpinfo)
  }
})

beaconSocket.on('error', (err) => {
  console.error('Error: %s', err.stack || err.message || err)
})

function getNetworkInterfaces() {
  const interfaces = os.networkInterfaces()

  return Object.keys(interfaces)
    .map(name => interfaces[name].map(ifaceinfo => ({ name: name, ...ifaceinfo })))
    .reduce((agg, arr) => agg.concat(arr), [])
}

function getMulticastAddresses() {
  return getNetworkInterfaces()
    .filter(iface => !iface.internal)
    .filter(iface => iface.family === 'IPv4')
    .map(iface => iface.address)
    // .map(iface => [...iface.address.split('.').slice(0, 3), '255'].join('.'))
}

function ensureSocket(address) {
  if (!socketCache[address]) {
    const socket = net.createConnection(COMMAND_PORT, address)
    socket.setNoDelay(true)

    socketCache[address] = new Promise((resolve, reject) => {
      socket.on('connect', function () {
        console.log('Connected.')

        resolve(socket)
      })

      socket.on('data', function (chunk) {
        console.log('Chunk: %s', chunk)
      })

      socket.on('end', function () {
        console.log('Disconnected.')

        socketCache[address] = null
      })

      socket.on('close', function () {
        console.log('Closed.')
      })

      socket.on('error', function (err) {
        console.log('Error:', err)
      })
    })
  }

  return socketCache[address]
}

function sendCommand(address) {
  ensureSocket(address)
    .then(socket => socket.write('\0'))
}

beaconSocket.on('listening', () => {
  var info = beaconSocket.address()
  console.log('Listening on %s:%s', info.address, info.port)

  beaconSocket.setBroadcast(true);
  getMulticastAddresses()
    .forEach(addr => beaconSocket.addMembership(MULTICAST_ADDRESS, addr))
})
beaconSocket.bind(BEACON_PORT)
