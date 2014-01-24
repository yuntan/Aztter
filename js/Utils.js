.pragma library

var monthMap = { "Jan": 0, "Feb": 1, "Mar": 2, "Apr": 3,
    "May": 4, "Jun": 5, "Jul": 6, "Aug": 7,
    "Sep": 8, "Oct": 9, "Nov": 10, "Dec": 11 }

// returns local time
function parseCreatedAt(createdAt) {
    console.log("createdAt = " + createdAt)
    var array1 = createdAt.split(' ')
    var array2 = array1[3].split(':')

    var ret = new Date()
    var offset = ret.getTimezoneOffset() / 60
    console.log("timezone offset = " + offset)
    if(array2[0] - offset < 0) {
        array1[2]--
        array2[0] += (24 - offset)
    }
    else if(array2[0] - offset > 24){
        array1[2]++
        array2[0] -= (24 + offset)
    }
    else {
        array2[0] -= offset
    }

    ret.setFullYear(array1[5], monthMap[array1[1]], array1[2])
    ret.setHours(array2[0], array2[1], array2[2])
    console.log("ret = " + ret)
    return ret
}

function dateToStr(createdAt) {
    // FIXME
    var now = new Date()
    console.log("now = " + now.getTime() + " createdAt = " + createdAt.getTime())
    var diff = Math.floor((now.getTime() - createdAt.getTime()) / 1000)
    if(diff >= 86400)
        return Math.floor(diff / 86400) + qsTr(" days ago")
    if(diff >= 3600)
        return Math.floor(diff / 3600) + qsTr(" hours ago")
    if(diff >= 60)
        return Math.floor(diff / 60) + qsTr(" minutes ago")
    if(diff >= 10)
        return diff + qsTr(" seconds ago")
    return qsTr("Just now")
}
