Release Process and Checklist
========================================

.. note::

   This information is only useful if you are a developer of botan who
   is creating a new release of the library.

Pre Release Checks
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Confirm that the release notes under ``doc/relnotes`` are accurate and
complete. Then update the datestamp in the release notes and in
``readme.txt`` and ``botan_version.py`` (also checking that the
version is correct in those files), and change the entry for the
appropriate branch in ``doc/download.rst`` to point to the new
release. Check in these changes (alone, with no other modifications)
with a checkin message along the lines of "Update for X.Y.Z release",
then tag the release with the version in monotone (eg tag '1.11.8', no
prefix).

Build The Release
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The release script is ``src/build-data/scripts/dist.py`` and runs from
a monotone repository by pulling the revision matching the tag set
previously. For instance::

 $ src/build-data/scripts/dist.py --mtn-db ~/var/mtn/botan.mtn 1.11.8

The ``--mtn-db`` 'option' is mandatory, unless the environmental
variable ``BOTAN_MTN_DB`` is set, in which case that value is used if
``--mtn-db`` is not provided.

Another useful option is ``--output-dir``, which specifies where
the output will be placed.

The ``--pgp-key-id`` option is used to specifiy a PGP keyid. If set,
the script assumes that it can execute GnuPG and will attempt to
create signatures for the tarballs. The default value is ``EFBADFBC``,
matching :doc:`the official signing key <pgpkey>`. You can set it to
an empty value (``--pgp-key-id=``) to avoid creating signatures though
official distributed releases *should not* be released without
signatures.

Build The Windows Installer
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

On Windows, run ``configure.py`` to setup a build::

 $ python ./configure.py --cc=msvc --cpu=$ARCH --enable-ssse3

The ``--enable-ssse3`` looks unsafe, but in fact under Visual C++ we
do not compile with any special CPU specific flags, so this merely has
the effect of enabling support for SSE2/SSSE3 optimizations which will
only be used if ``cpuid`` indicates they are supported.

After completing the build (and running the tests), use `InnoSetup
<http://www.jrsoftware.org/isinfo.php>`_ to create the installer.  A
InnoSetup script is created from ``src/build-data/innosetup.in`` and
placed in ``build/botan.iss`` by ``configure.py``. Create the
installer either via the InnoSetup GUI by opening the ``iss`` file and
selecting the 'Compile' option, or using the ``iscc`` command line
tool. If all goes well it will produce an executable with a name like
``botan-1.11.8-x86_64.exe``. Sign the installers with GPG.

Update The Website
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The current botan website is derived entirely from the ReST content in
``docs`` using Sphinx (plus Doxygen generated documentation). A script
called ``mtn-watch`` periodically checks for new updates on the
``net.randombit.botan`` branch (only), and if found regenerates the
site content. Thus as soon as the changes are synced to the server
running on ``randombit.net``, the website will be updated.

Announce The Release
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Send an email to the announce and devel mailing lists noting that a
new release is available.

Post Release Process
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Immediately after the new release is created, update
``botan_version.py`` and ``readme.txt`` once again, incrementing the
version number as appropriate and removing the release dates. For
release notes, use "Not Yet Released" as the placeholder. For
``botan_version.py``, use 0.
