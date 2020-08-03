const {
    fromZigbeeConverters
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

const device = {
    zigbeeModel: ['DIYRuZ_Reed'],
    model: 'DIYRuZ_Reed',
    vendor: 'DIYRuZ',
    description: '[Reed switch](http://xxx.ru)',
    supports: '',
    fromZigbee: [
        withEpPreffix(fromZigbeeConverters.on_off),
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
                'genOnOff'
            ]);
        };
    },
};

module.exports = device;