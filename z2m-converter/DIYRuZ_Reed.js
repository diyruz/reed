const {
    fromZigbeeConverters,
    exposes
} = require('zigbee-herdsman-converters');


const bind = async (endpoint, target, clusters) => {
    for (const cluster of clusters) {
        await endpoint.bind(cluster, target);
    }
};

const withEpPreffix = (converter) => ({
    ...converter,
    convert: (model, msg, publish, options, meta) => {
        const epID = msg.endpoint.ID;
        const converterResults = converter.convert(model, msg, publish, options, meta);
        return Object.keys(converterResults)
            .reduce((result, key) => {
                result[`${key}_${epID}`] = converterResults[key];
                return result;
            }, {});
    },
});

const contactDiscovery = {
    type: 'binary_sensor',
    object_id: 'contact',
    discovery_payload: {
        payload_on: true,
        payload_off: false,
        value_template: '{{ value_json.contact }}',
    },
};

const batteryDiscovery = {
    type: 'sensor',
    object_id: 'battery',
    discovery_payload: {
        value_template: '{{ value_json.battery }}',
        unit_of_measurement: '%',
        device_class: 'battery',
    },
};

const voltageDiscovery = {
    type: 'sensor',
    object_id: 'voltage',
    discovery_payload: {
        value_template: '{{ value_json.voltage }}',
        unit_of_measurement: 'mV',
        device_class: 'voltage',
    },
};

const linkqualityDiscovery = {
    type: 'sensor',
    object_id: 'linkquality',
    discovery_payload: {
        value_template: '{{ value_json.linkquality }}',
        unit_of_measurement: 'lqi',
        icon: 'mdi:signal',
    },
};

const device = {
    zigbeeModel: ['DIYRuZ_Reed'],
    model: 'DIYRuZ_Reed',
    vendor: 'DIYRuZ',
    description: '[Reed switch](http://xxx.ru)',
    supports: '',
    fromZigbee: [
        fromZigbeeConverters.ias_contact_alarm_1,
        fromZigbeeConverters.battery,
    ],
    toZigbee: [],
    meta: {
        configureKey: 1,
        disableDefaultResponse: true,
    },
    configure: async (device, coordinatorEndpoint) => {
        for (ep of [1, 2, 3]) {
            await bind(device.getEndpoint(ep), coordinatorEndpoint, [
                'genPowerCfg',
                'ssIasZone'
            ]);
        };
    },
    homeassistant: [
        contactDiscovery,
        batteryDiscovery,
        voltageDiscovery,
        linkqualityDiscovery
    ],
    exposes: [
        exposes.presets.contact(),
        exposes.presets.battery(),
        exposes.presets.voltage(),
        exposes.presets.linkquality()
    ]
};

module.exports = device;
