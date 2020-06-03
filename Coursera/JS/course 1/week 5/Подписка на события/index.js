var eventDatabase = {};


module.exports = {

    /**
     * @param {String} event
     * @param {Object} subscriber
     * @param {Function} handler
     */
    on: function (event, subscriber, handler) {
        if (!eventDatabase.hasOwnProperty(event))
        {
            eventDatabase[event] = [];
        }
        eventDatabase[event].push({
            name: subscriber,
            handler: handler.bind(subscriber)
        });
        return this;
    },

    /**
     * @param {String} event
     * @param {Object} subscriber
     */
    off: function (event, subscriber) {
        if (!eventDatabase.hasOwnProperty(event))
        {
            return this;
        }

        eventDatabase[event] = eventDatabase[event].filter(function (record) {
            return !(record.name === subscriber);
        });
        if (eventDatabase[event].length === 0)
        {
            delete eventDatabase[event];
        }
        return this;
    },

    /**
     * @param {String} event
     */
    emit: function (event) {
        if (!eventDatabase.hasOwnProperty(event))
        {
            return this;
        }
        eventDatabase[event].forEach(function (record) {
            record.handler();
        });

        return this;
    }
};
