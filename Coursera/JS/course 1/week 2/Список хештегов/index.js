
function isHashTag(word, _)
{
    return word[0]==='#';
}

function deleteHashTabSymbol(tag, _)
{
    return tag.slice(1);
}
/**
 * @returns {String[]}
 * @param tweet
 */
module.exports = function (tweet)
{
    return tweet.split(' ').filter(isHashTag).map(deleteHashTabSymbol);
};
