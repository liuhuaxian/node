# About Pungi

Pungi Logo is a distribution compose tool.

Composes are release snapshots that contain release deliverables such as:

    installation trees
        RPMs
        repodata
        comps
    (bootable) ISOs
    kickstart trees
        anaconda images
        images for PXE boot

Tool overview

Pungi consists of multiple separate executables backed by a common library.

The main entry-point is the pungi-koji script. It loads the compose configuration and kicks off the process. Composing itself is done in phases. Each phase is responsible for generating some artifacts on disk and updating the compose object that is threaded through all the phases.

Pungi itself does not actually do that much. Most of the actual work is delegated to separate executables. Pungi just makes sure that all the commands are invoked in the appropriate order and with correct arguments. It also moves the artifacts to correct locations.

The executable name pungi-koji comes from the fact that most of those separate executables submit tasks to Koji that does the actual work in an auditable way.

However unlike doing everything manually in Koji, Pungi will make sure you are building all images from the same package set, and will produce even deliverables that Koji can not create like YUM repos and installer ISOs.
Links

    Upstream GIT: https://pagure.io/pungi/
    Issue tracker: https://pagure.io/pungi/issues
    Questions can be asked on #fedora-releng IRC channel on FreeNode

Origin of name

The name Pungi comes from the instrument used to charm snakes. Anaconda being the software Pungi was manipulating, and anaconda being a snake, led to the referential naming.

The first name, which was suggested by Seth Vidal, was FIST, Fedora Installation <Something> Tool. That name was quickly discarded and replaced with Pungi.

There was also a bit of an inside joke that when said aloud, it could sound like punji, which is a sharpened stick at the bottom of a trap. Kind of like software…

# Phases

Each invocation of `pungi-koji` consists of a set of phases.

![phases](图片\phases.svg)

Most of the phases run sequentially (left-to-right in the diagram), but there are use cases where multiple phases run in parallel. This happens for phases whose main point is to wait for a Koji task to finish.

## Init

The first phase to ever run. Can not be skipped. It prepares the comps files for variants (by filtering out groups and packages that should not be there). See [Processing comps files](https://docs.pagure.org/pungi/comps.html) for details about how this is done.

## Pkgset

This phase loads a set of packages that should be composed. It has two separate results: it prepares repos with packages in `work/` directory (one per arch) for further processing, and it returns a data structure with mapping of packages to architectures.

## Buildinstall

Spawns a bunch of threads, each of which runs either `lorax` or `buildinstall` command (the latter coming from `anaconda` package). The commands create `boot.iso` and other boot configuration files. The image is finally linked into the `compose/` directory as netinstall media.

The created images are also needed for creating live media or other images in later phases.

With `lorax` this phase runs one task per variant.arch combination. For `buildinstall` command there is only one task per architecture and `product.img` should be used to customize the results.

## Gather

This phase uses data collected by `pkgset` phase and figures out what packages should be in each variant. The basic mapping can come from comps file, a JSON mapping or `additional_packages` config option. This inputs can then be enriched by adding all dependencies. See [Gathering packages](https://docs.pagure.org/pungi/gathering.html) for details.

Once the mapping is finalized, the packages are linked to appropriate places and the `rpms.json` manifest is created.

## ExtraFiles

This phase collects extra files from the configuration and copies them to the compose directory. The files are described by a JSON file in the compose subtree where the files are copied. This metadata is meant to be distributed with the data (on ISO images).

## Createrepo

This phase creates RPM repositories for each variant.arch tree. It is actually reading the `rpms.json` manifest to figure out which packages should be included.

## OSTree

Updates an ostree repository with a new commit with packages from the compose. The repository lives outside of the compose and is updated immediately. If the compose fails in a later stage, the commit will not be reverted.

Implementation wise, this phase runs `rpm-ostree` command in Koji runroot (to allow running on different arches).

## Createiso

Generates ISO files and accumulates enough metadata to be able to create `image.json` manifest. The file is however not created in this phase, instead it is dumped in the `pungi-koji` script itself.

The files include a repository with all RPMs from the variant. There will be multiple images if the packages do not fit on a single image.

The image will be bootable if `buildinstall` phase is enabled and the packages fit on a single image.

There can also be images with source repositories. These are never bootable.

## ExtraIsos

This phase is very similar to `createiso`, except it combines content from multiple variants onto a single image. Packages, repodata and extra files from each configured variant are put into a subdirectory. Additional extra files can be put into top level of the image. The image will be bootable if the main variant is bootable.

## LiveImages, LiveMedia

Creates media in Koji with `koji spin-livecd`, `koji spin-appliance` or `koji spin-livemedia` command. When the media are finished, the images are copied into the `compose/` directory and metadata for images is updated.

## ImageBuild

This phase wraps up `koji image-build`. It also updates the metadata ultimately responsible for `images.json` manifest.

## OSBS

This phase builds docker base images in [OSBS](http://osbs.readthedocs.io/en/latest/index.html).

The finished images are available in registry provided by OSBS, but not downloaded directly into the compose. The is metadata about the created image in `compose/metadata/osbs.json`.

## OSTreeInstaller

Creates bootable media that carry an ostree repository as a payload. These images are created by running `lorax` with special templates. Again it runs in Koji runroot.

## Repoclosure

Run `repoclosure` on each repository. By default errors are only reported in the log, the compose will still be considered a success. The actual error has to be looked up in the compose logs directory. Configuration allows customizing this.

## ImageChecksum

Responsible for generating checksums for the images. The checksums are stored in image manifest as well as files on disk. The list of images to be processed is obtained from the image manifest. This way all images will get the same checksums irrespective of the phase that created them.

## Test

This phase is supposed to run some sanity checks on the finished compose.

The only test is to check all images listed the metadata and verify that they look sane. For ISO files headers are checked to verify the format is correct, and for bootable media a check is run to verify they have properties that allow booting.