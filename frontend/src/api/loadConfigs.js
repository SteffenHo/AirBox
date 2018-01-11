export default function loadConfigs() {
    return Promise.resolve([
        {
            "id": 15,
            "name": "test-on",
            "deviceId": 1,
            "config": {
                "decimal": 1381717,
                "bitLength": 24,
                "pulseLength": 424,
                "protocol": 1
            }
        },
        {
            "id": 16,
            "name": "test-off",
            "deviceId": 1,
            "config": {
                "decimal": 1381716,
                "bitLength": 24,
                "pulseLength": 424,
                "protocol": 1
            }
        }
    ]);

    return fetch('http://airbox/devices/configs', {
        headers: {
            'Cache-Control': 'no-cache',
        }
    }).then(res => {
        if(res.statusCode === 200) {
            return res.json();
        }

        return res.text();
    });
}
