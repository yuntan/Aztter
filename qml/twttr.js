.pragma library

Qt.include("twitter-text.js")

function autoLink(text, options) {
	return twttr.txt.autoLink(text, options)
}
