
/**
 * @param {String[]} hashtags
 * @returns {String}
 */
module.exports = function (hashtags) {
    var unique = hashtags.reduce(function (acc, item)
    {
        acc[item.toLowerCase()] = 0;
        return acc;
    },
        {})
    return Object.keys(unique).join(', ');
};
