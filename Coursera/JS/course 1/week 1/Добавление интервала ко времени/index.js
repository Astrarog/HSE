/**
 * @param {Number} hours
 * @param {Number} minutes
 * @param {Number} interval
 * @returns {String}
 */
module.exports = function (hours, minutes, interval) {
    var newMinutes = (minutes + interval)%60;
    var newHours = (hours + Math.floor((minutes + interval)/60))%24;
    var strMin = String(newMinutes);
    var strHour = String(newHours);
    if(newMinutes<10)
    {
        strMin = '0'+strMin;
    }
    if(strHour<10)
    {
        strHour = '0'+strHour;
    }
    return strHour+':'+strMin;
};
