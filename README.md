# Output

Published Website is accessible at this address: https://monge.univ-eiffel.fr/~marsault/cpp/cours/.

# Usage

## Tools

This site is built with [Hugo](https://gohugo.io/documentation/).  
You need to install the tool in order to rebuild the site locally.

## Sources

To obtain the sources:
```b
git clone https://github.com/marsault/CPP_Learning.git  
git submodule update --init --recursive
```

## Testing

Once you have made some changes to the sources, you can test your modifications locally by running:  
```b
# from directory CPP_Learning
hugo server
```

The website is built in `public/` and accessible locally on http://localhost:1313/.

## Publishing

The github is used to automatically build the website on specific branches:
- a push on `master` updates branch `gh-pages` . See https://github.com/marsault/CPP_Learning/actions/workflows/hugo.yml .
- a push on `next` updates branch `generated-pages-next`. See https://github.com/marsault/CPP_Learning/actions/workflows/autogen-next.yml .


## Deployment

We use a *shallow clone* on the web server to minimize the size of the website. For instance, to deploy the website in directory `<directory>`, we use: 
```
git clone https://github.com/marsault/CPP_Learning/ --branch <branch> --single-branch <directory>
```
where `<branch>` is either `gh-pages` or `generated-pages-next` in our case.


Then, we use the following script to update the shallow clone.

```bash title='update_shallow_clone.sh'
#!/bin/bash

if [[ $# -ne 2 ]] ; then
  echo "Illegal number of arguments (2 expected)"
  echo "Usage: update_shallow_clone.sh <directory> <branch>"
  exit 1
fi

GIT_DIR=$1
BRANCH=$2

echo "================================================================================"
echo "Updating directory ${GIT_DIR} from branch ${BRANCH}"
echo "================================================================================"
echo "date: $(date)"

echo ""
echo "1. fetch --depth 1"
(cd ${GIT_DIR} && git fetch --depth 1)

echo ""
echo "2a. git rev-parse HEAD"
local_commit=$(cd ${GIT_DIR} && git rev-parse HEAD)
echo ${local_commit}

echo ""
echo "2b. git rev-parse @{u}"
distant_commit=$(cd ${GIT_DIR} && git rev-parse @{u})
echo ${distant_commit}

echo ""
if [ "${local_commit}" == "${distant_commit}" ]
then
  echo "Nothing to update."
else
  echo "3. git reset --hard origin/${BRANCH}"
  (cd ${GIT_DIR} && git reset --hard origin/${BRANCH})
  echo "Repository updated."
fi
(cd ${GIT_DIR} && git log -1 --format="%at" | xargs -I{} date -d @{} "+Last commit on %Y/%m/%d at %H:%M")

```